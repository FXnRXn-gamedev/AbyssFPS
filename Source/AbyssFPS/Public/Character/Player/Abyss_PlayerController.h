// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "Abyss_PlayerController.generated.h"

class AAbyss_PlayerCharacter;
class UInputMappingContext;
class UInputAction;
class UAbilitySystemComponent;






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
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void AcknowledgePossession(class APawn* P) override;
	
	
	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Input")
	UInputMappingContext* DefaultAbyssMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Input|Action")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Input|Action")
	UInputAction* LookAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Input|Action")
	UInputAction* JumpAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Input|Action")
	UInputAction* SprintAction;
	
	
	// Settings
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Settings")
	float MouseSensitivity = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Settings")
	bool bInvertYAxis = false;
	
	
	// Accessors
	UFUNCTION()
	AAbyss_PlayerCharacter* GetTAbyssCharacter() const;

	UFUNCTION()
	UAbilitySystemComponent* GetAbilitySystemComponent() const;
	
	// =================================================================================================================
protected:
	// Input handlers
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_Jump_Started(const FInputActionValue& InputActionValue);
	void Input_Jump_Completed(const FInputActionValue& InputActionValue);
	void Input_Sprint_Started(const FInputActionValue& InputActionValue);
	void Input_Sprint_Completed(const FInputActionValue& InputActionValue);
	
	
	// Send ability input to GAS
	void SendLocalInputToASC(bool bPressed, int32 InputID);
	
	// Cached Character
	UPROPERTY()
	AAbyss_PlayerCharacter* CachedCharacter;
	
};


