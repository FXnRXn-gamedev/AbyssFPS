// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Character/Player/Abyss_PlayerController.h"
#include "Abyss_GameplayAbilityBase.generated.h"



class AAbyss_PlayerCharacter;


UENUM(BlueprintType)
enum class EAbyss_AbilityActivationPolicy : uint8
{
	OnInputTrigger, // Try to activate when input is triggered
	WhileInputActive, // Continually try to activate while input is active
	OnSpawn // Activate immediately when granted
};

UENUM(BlueprintType)
enum class EAbyss_AbilityInputID : uint8
{
	None				UMETA(DisplayName = "None"),
	Confirm				UMETA(DisplayName = "Confirm"),
	Cancel				UMETA(DisplayName = "Cancel"),
	Jump				UMETA(DisplayName = "Jump"),
	Sprint				UMETA(DisplayName = "Sprint"),
	Crouch				UMETA(DisplayName = "Crouch"),
	Slide				UMETA(DisplayName = "Slide"),
	Fire				UMETA(DisplayName = "Fire"),
	ADS					UMETA(DisplayName = "Aim Down Sights"),
	Reload				UMETA(DisplayName = "Reload"),
	Heal				UMETA(DisplayName = "Heal"),
	Granade				UMETA(DisplayName = "Granade"),
	Ability1			UMETA(DisplayName = "Ability 1"),
	Ability2			UMETA(DisplayName = "Ability 2"),
	Ultimate			UMETA(DisplayName = "Ultimate"),
	Melee				UMETA(DisplayName = "Melee"),
	Interact			UMETA(DisplayName = "Interact")
};







UCLASS(Abstract)
class ABYSSFPS_API UAbyss_GameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	//------------------------------------------------------------------------------------------------------------------
public:
	UAbyss_GameplayAbilityBase();
	
	// Get Ability Level
	UFUNCTION()
	int32 Get_AbilityLevel() const;
	
	// Get Avatar
	UFUNCTION()
	AAbyss_PlayerCharacter* Get_AbyssPlayerCharacter() const;
	
	// Get Player Controller
	UFUNCTION()
	AAbyss_PlayerController* Get_AbyssPlayerController() const;
	
	// Get ASC from avatar
	UFUNCTION()
	UAbilitySystemComponent* Get_AbilitySystemComponentFromAvatar() const;
	
	
	//--> TODO : COOLDOWN
	
	
	//
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Ability")
	EAbyss_AbilityActivationPolicy ActivationPolicy = EAbyss_AbilityActivationPolicy::OnInputTrigger;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Ability")
	EAbyss_AbilityInputID AbilityInputID = EAbyss_AbilityInputID::None;
	
	
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	
	
	
	
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Ability")
	bool bServerOnly = false;
	
};
