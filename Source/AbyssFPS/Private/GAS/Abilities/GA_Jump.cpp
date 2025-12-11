// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "GAS/Abilities/GA_Jump.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Character/Player/Abyss_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utility/Abyss_DebugHelper.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

UGA_Jump::UGA_Jump()
{
	AbilityInputID = EAbyss_AbilityInputID::Jump;
	ActivationPolicy = EAbyss_AbilityActivationPolicy::OnInputTrigger;
	
	// Ability Tags
	// AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));
	SetAssetTags(AssetTags);

	// Tags Applied while jumping
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Jumping"));

	// Cannot jump while these are active
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Dead"));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Downed"));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag("State.Stunned"));
	
	// Instancing policy
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	// Network settings
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	bReplicateInputDirectly = true;
}




// =====================================================================================================================
// ---> GAS <---
// =====================================================================================================================
void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}
	
	AAbyss_PlayerCharacter* PlayerCharacter = Get_AbyssPlayerCharacter();
	if (!PlayerCharacter)
	{
		K2_EndAbility();
		return;
	}
	
	// If on ground, reset jump count
	if (IsOnGround()) CurrentJumpCount = 0;
	
	// Perform jump
	PerformJump();
	
	// Increment jump count
	CurrentJumpCount++;
	
	// Play jump effects
	PlayJumpEffects();
	
	// TODO : Apply in-air effects if specified
	
	// Start waiting for landing
	StartWaitingForLanding();
}

void UGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (Character) Character->StopJumping();
	
}

bool UGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;
	
	const AAbyss_PlayerCharacter* PlayerCharacter = Cast<AAbyss_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!PlayerCharacter) return false;
	
	const UCharacterMovementComponent* MovementComp = PlayerCharacter->GetCharacterMovement();
	if (!MovementComp) return false;
	
	// Check if can jump while crouching
	if (!bCanJumpWhileCrouching && MovementComp->IsCrouching()) return false;
	
	// Check jump count for multi-jump
	if (MovementComp->IsFalling())
	{
		// In-air check if we have jumps remaining
		UGA_Jump* MutableThis = const_cast<UGA_Jump*>(this);
		if (MutableThis->CurrentJumpCount >= MaxJumpCount) return false;
	}
	
	// Check if movement mode allows jumping
	if (MovementComp->MovementMode == MOVE_None || MovementComp->MovementMode == MOVE_Custom) return false;
	
	
	
	return true;
}

void UGA_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                          const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// Clean up
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (Character) Character->LandedDelegate.RemoveDynamic(this, &UGA_Jump::OnLanded);
	
	// TODO : In-air effect if still active
	
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}




// =====================================================================================================================
// ---> JUMP FUNCTIONALITY <---
// =====================================================================================================================



void UGA_Jump::OnLanded(const FHitResult& Hit)
{
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (Character)
	{
		Character->LandedDelegate.RemoveDynamic(this, &ThisClass::OnLanded);
	}
	
	// Reset jump count
	CurrentJumpCount = 0;
	
	// TODO : Play landing effects
	// TODO : Remove In-air effects
	
	// End ability
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGA_Jump::PerformJump()
{
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (!Character) return;
	
	UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();
	if (!MovementComp) return;
	
	// Calculate jump velocity with potential modifiers from attributes
	float FinalJumpVelocity = JumpZVelocity;
	
	// Check for jump height modifiers from attributes
	UAbilitySystemComponent* ASC = Get_AbilitySystemComponentFromAvatar();
	if (ASC)
	{
		// Could add a JumpHeight attribute for buff systems
		// float JumpMod = ASC->GetNumericAttribute(...);
		// FinalJumpVelocity *= JumpMod;
	}
	
	// If crouching, uncrouch first
	if (MovementComp->IsCrouching())
	{
		Character->UnCrouch();
	}
	
	// Perform jump based on current state
	if (MovementComp->IsMovingOnGround())
	{
		// Ground jump
		MovementComp->JumpZVelocity = FinalJumpVelocity;
		MovementComp->AirControl = AirControl;
		Character->Jump();
	}
	else if (MovementComp->IsFalling() && CurrentJumpCount < MaxJumpCount)
	{
		// Air jump (double jump, etc.)
		FVector CurrentVelocity = MovementComp->Velocity;
		CurrentVelocity.Z = FinalJumpVelocity;
		MovementComp->Velocity = CurrentVelocity;
		
		// TODO : Play air jump specific effects
	}
	
	// Broadcast jump event
	FGameplayEventData EventData;
	EventData.Instigator = Character;
	EventData.EventMagnitude = CurrentJumpCount;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Character,
		FGameplayTag::RequestGameplayTag(FName("Event.Movement.Jump")),
		EventData
	);
	
}

void UGA_Jump::PlayJumpEffects()
{
}

void UGA_Jump::PlayLandEffects(const FHitResult& Hit)
{
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (!Character) return;
	
	FVector LandLocation = Hit.ImpactPoint;
	
	// Calculate land intensity based on fall velocity
	UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();
	float FallSpeed = FMath::Abs(MovementComp ? MovementComp->Velocity.Z : 0.0f);
	float LandIntensity = FMath::Clamp(FallSpeed / 1000.0f, 0.0f, 1.0f);
	
	// Broadcast land event
	FGameplayEventData EventData;
	EventData.Instigator = Character;
	EventData.EventMagnitude = LandIntensity;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		Character,
		FGameplayTag::RequestGameplayTag(FName("Event.Movement.Landed")),
		EventData
	);
}

bool UGA_Jump::IsOnGround() const
{
	const AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (!Character) return false;
	
	const UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();
	if (!MovementComp) return false;
	
	return MovementComp->IsMovingOnGround();
	
}

void UGA_Jump::StartWaitingForLanding()
{
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (!Character) return;
	
	// Bind to landed delegate
	UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();
	if (MovementComp)
	{
		Character->LandedDelegate.AddDynamic(this, &UGA_Jump::OnLanded);
	}
}
