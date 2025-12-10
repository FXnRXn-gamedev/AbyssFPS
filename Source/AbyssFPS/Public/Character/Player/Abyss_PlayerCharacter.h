// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "AbyssFPS/Public/Character/Abyss_BaseCharacter.h"
#include "AbilitySystemInterface.h"
#include "Abyss_PlayerCharacter.generated.h"


class UCameraComponent;
class UAbilitySystemComponent;
class UAbyss_AttributeSet;
class UGameplayAbility;
class UGameplayEffect;









UCLASS()
class ABYSSFPS_API AAbyss_PlayerCharacter : public AAbyss_BaseCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	// =================================================================================================================
public:
	AAbyss_PlayerCharacter();
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	
	
	// IAbilitySystemInterface inplementation
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	
	
#pragma region Components
	
	// Components
	UPROPERTY(VisibleAnywhere, Category = "---Abyss---|Components")
	UCameraComponent* CameraComponent;
#pragma endregion 
	
#pragma region GAS
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|GAS")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|GAS")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	
#pragma endregion 

#pragma region Settings
	// Settings
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Settings")
	float DefaultFOV = 90.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Settings")
	float SprintSpeed = 800.0f;

	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Settings")
	float WalkSpeed = 400.0f;
	
#pragma endregion
	
	
	
	
	
	
	
	// Input handling
	void HandleMoveInput(const FVector2D& MoveInput);
	void HandleLookInput(const FVector2D& LookInput);
	
	// =================================================================================================================
protected:
	// Ability system (obtained from PlayerState)
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY()
	UAbyss_AttributeSet* AttributeSet;
	
	// Initialization
	void InitializeAbilitySystem();
	void GiveDefaultAbilities();
	void ApplyDefaultAttributes();
	
};
