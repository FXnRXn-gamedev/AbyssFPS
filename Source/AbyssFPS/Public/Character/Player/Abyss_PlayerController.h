// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Abyss_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;







UCLASS()
class ABYSSFPS_API AAbyss_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	// =================================================================================================================
public:
	AAbyss_PlayerController();
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	
	
	// Input Actions
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "---Abyss---|Input")
	UInputMappingContext* DefaultAbyssMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "---Abyss---|Input|Action")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "---Abyss---|Input|Action")
	UInputAction* LookAction;
	
	// =================================================================================================================
protected:
	// Input handlers
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	
};
