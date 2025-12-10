// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "AbyssFPS/Public/Core/Abyss_PlayerState.h"

#include "GAS/Attributes/Abyss_AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Character/Player/Abyss_PlayerCharacter.h"
#include "Utility/Abyss_DebugHelper.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================


AAbyss_PlayerState::AAbyss_PlayerState()
{
	// Create Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	// Create Attribute Set
	AttributeSet = CreateDefaultSubobject<UAbyss_AttributeSet>(TEXT("AttributeSet"));
	
	// Network update frequency
	SetNetUpdateFrequency(100.f);
}


// =====================================================================================================================
// ---> NET <---
// =====================================================================================================================

void AAbyss_PlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}


// =====================================================================================================================
// ---> GAS <---
// =====================================================================================================================

void AAbyss_PlayerState::InitializeAbilitySystem(class AAbyss_PlayerCharacter* InOwner)
{
	if (!IsValid(AbilitySystemComponent) && !InOwner) return;
	
	AbilitySystemComponent->InitAbilityActorInfo(this, InOwner);
	if (AttributeSet) AbilitySystemComponent->AddSpawnedAttribute(AttributeSet);
}

void AAbyss_PlayerState::GiveAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level)
{
	if (!IsValid(AbilitySystemComponent) || !AbilityClass) return;

	if (HasAuthority())
	{
		FGameplayAbilitySpec Spec(AbilityClass, Level, INDEX_NONE, this);
		FGameplayAbilitySpecHandle AbilitySpecHandle = AbilitySystemComponent->GiveAbility(Spec);
		GrantedAbilities.Add(AbilitySpecHandle);
	}
}

void AAbyss_PlayerState::RemoveAbility(TSubclassOf<UGameplayAbility> AbilityClass)
{
	if (!IsValid(AbilitySystemComponent) || !AbilityClass) return;
	
	if (HasAuthority())
	{
		FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromClass(AbilityClass);
		if (Spec)
		{
			AbilitySystemComponent->ClearAbility(Spec->Handle);
			GrantedAbilities.Remove(Spec->Handle);
		}
	}
}

UAbilitySystemComponent* AAbyss_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


