// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "AbyssFPS/Public/Character/Player/Abyss_PlayerCharacter.h"

#include "Components/CapsuleComponent.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

AAbyss_PlayerCharacter::AAbyss_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Configure capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 98.f);
}




// =====================================================================================================================
// ---> LOCOMOTION HANDLING <---
// =====================================================================================================================

void AAbyss_PlayerCharacter::HandleMoveInput(const FVector2D& MoveInput)
{
}

void AAbyss_PlayerCharacter::HandleLookInput(const FVector2D& LookInput)
{
}