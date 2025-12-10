// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "GAS/Abilities/Abyss_GameplayAbilityBase.h"

#include "AbilitySystemComponent.h"
#include "Character/Player/Abyss_PlayerCharacter.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================
UAbyss_GameplayAbilityBase::UAbyss_GameplayAbilityBase()
{
	// Default Settings
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;
	
	// Default activation blocked tags
	
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("State.Stunned")));

}


// =====================================================================================================================
// ---> GAS<---
// =====================================================================================================================

void UAbyss_GameplayAbilityBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	// Auto-activate on spawn if set
	if (ActivationPolicy == EAbyss_AbilityActivationPolicy::OnSpawn)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}

void UAbyss_GameplayAbilityBase::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
}


// =====================================================================================================================
// ---> HELPER <---
// =====================================================================================================================

int32 UAbyss_GameplayAbilityBase::Get_AbilityLevel() const
{
	if (CurrentActorInfo && CurrentSpecHandle.IsValid())
	{
		return Super::GetAbilityLevel(CurrentSpecHandle, CurrentActorInfo);
	}
	return 1;
}

AAbyss_PlayerCharacter* UAbyss_GameplayAbilityBase::Get_AbyssPlayerCharacter() const
{
	if(CurrentActorInfo) return Cast<AAbyss_PlayerCharacter>(CurrentActorInfo->AvatarActor.Get());
	return nullptr;
}

AAbyss_PlayerController* UAbyss_GameplayAbilityBase::Get_AbyssPlayerController() const
{
	if (CurrentActorInfo) return Cast<AAbyss_PlayerController>(CurrentActorInfo->PlayerController.Get());
	return nullptr;
}

UAbilitySystemComponent* UAbyss_GameplayAbilityBase::Get_AbilitySystemComponentFromAvatar() const
{
	return GetAbilitySystemComponentFromActorInfo();
}


