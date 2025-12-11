// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "GAS/Abilities/GA_Sprint.h"

#include "Character/Player/Abyss_PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

UGA_Sprint::UGA_Sprint()
{
	AbilityInputID = EAbyss_AbilityInputID::Sprint;
	ActivationPolicy = EAbyss_AbilityActivationPolicy::WhileInputActive;
	
	// Ability Tags
	FGameplayTagContainer AssetTags;
	AssetTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Sprint")));
	SetAssetTags(AssetTags);
	
	// Cannot sprint while these are active
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.ADS")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Firing")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Reloading")));
	
	// Cancel this when sprinting
	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.ADS")));
	
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}



// =====================================================================================================================
// ---> GAS <---
// =====================================================================================================================

void UGA_Sprint::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
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
	
	// Apply Sprint Speed
	UCharacterMovementComponent* MovementComp = PlayerCharacter->GetCharacterMovement();
	if (MovementComp) MovementComp->MaxWalkSpeed = SprintSpeed;
	
	
	// TODO : Apply Sprint Effetc if we have one
}

void UGA_Sprint::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	K2_EndAbility();
}

bool UGA_Sprint::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
                                    FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags)) return false;
	
	AAbyss_PlayerCharacter* Character = Cast<AAbyss_PlayerCharacter>(ActorInfo->AvatarActor.Get());
	if (!Character) return false;
	
	UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();
	if (MovementComp && MovementComp->Velocity.SizeSquared() < 100.0f) return false;
	
	return true;
}

void UGA_Sprint::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	AAbyss_PlayerCharacter* Character = Get_AbyssPlayerCharacter();
	if (Character)
	{
		UCharacterMovementComponent* MovementComp = Character->GetCharacterMovement();
		if (MovementComp)
		{
			MovementComp->MaxWalkSpeed = Character->WalkSpeed;
		}
	}
	
	
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


// =====================================================================================================================
// ---> LOGIC <---
// =====================================================================================================================

