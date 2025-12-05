// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbyssFPS/Public/Character/Abyss_BaseCharacter.h"
#include "Abyss_PlayerCharacter.generated.h"

UCLASS()
class ABYSSFPS_API AAbyss_PlayerCharacter : public AAbyss_BaseCharacter
{
	GENERATED_BODY()
	// =================================================================================================================
public:
	AAbyss_PlayerCharacter();
	
	
	
	
	
	// Input handling
	void HandleMoveInput(const FVector2D& MoveInput);
	void HandleLookInput(const FVector2D& LookInput);
	
};
