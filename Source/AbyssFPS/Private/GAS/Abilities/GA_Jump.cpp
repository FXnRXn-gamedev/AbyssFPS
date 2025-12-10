// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "GAS/Abilities/GA_Jump.h"

#include "Utility/Abyss_DebugHelper.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

UGA_Jump::UGA_Jump()
{
	AbilityInputID = EAbyss_AbilityInputID::Jump;
	ActivationPolicy = EAbyss_AbilityActivationPolicy::OnInputTrigger;
	
	// Ability Tags
	AbilityTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.Jump")));

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
	
	FString Msg = FString::Printf(TEXT("Jump Ability Activated"));
	Abyss_DebugHelper::DebugPrint(Msg);
}

void UGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
}

bool UGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGA_Jump::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                          const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
