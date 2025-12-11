// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abyss_GameplayAbilityBase.h"
#include "GA_Sprint.generated.h"


UCLASS()
class ABYSSFPS_API UGA_Sprint : public UAbyss_GameplayAbilityBase
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	UGA_Sprint();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
	
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo) override;
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayTagContainer* SourceTags = nullptr, 
		const FGameplayTagContainer* TargetTags = nullptr, 
		FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, bool bWasCancelled) override;
	
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	
#pragma region Settings
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Sprint")
	float SprintSpeed = 750.f;
	
#pragma endregion 
	
	
	
	
	
};
