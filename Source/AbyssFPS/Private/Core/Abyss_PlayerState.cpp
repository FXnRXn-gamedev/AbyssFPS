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

UAbilitySystemComponent* AAbyss_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


