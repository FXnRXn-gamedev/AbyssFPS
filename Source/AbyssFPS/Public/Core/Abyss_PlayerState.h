// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayAbilitySpec.h"


#include "Abyss_PlayerState.generated.h"



// Forward Decleration
class UAbilitySystemComponent;
class UAbyss_AttributeSet;
class UGameplayAbility;
class UGameplayEffect;







UCLASS()
class ABYSSFPS_API AAbyss_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	AAbyss_PlayerState();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Get IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// Get Attribute Set
	UAbyss_AttributeSet* GetAttributeSet() const { return AttributeSet; }
	
	// Ability System Setup
	void InitializeAbilitySystem(class AAbyss_PlayerCharacter* InOwner);
	
	// Grants an ability to the player
	UFUNCTION()
	void GiveAbility(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1);
	
	UFUNCTION()
	void RemoveAbility(TSubclassOf<UGameplayAbility> AbilityClass);
	
	// TODO : Applies a gameplay effect to the plater


	//------------------------------------------------------------------------------------------------------------------
protected:
	UPROPERTY(VisibleAnywhere, Category = "---Abyss---|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	UPROPERTY()
	UAbyss_AttributeSet* AttributeSet = nullptr;
	
	
	// Granted ability handles
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;
};
