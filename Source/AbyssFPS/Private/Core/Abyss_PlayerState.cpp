// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "AbyssFPS/Public/Core/Abyss_PlayerState.h"



// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================


AAbyss_PlayerState::AAbyss_PlayerState()
{
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


UAbilitySystemComponent* AAbyss_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
