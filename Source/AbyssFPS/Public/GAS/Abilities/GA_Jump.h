// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Abyss_GameplayAbilityBase.h"
#include "GA_Jump.generated.h"

/**
 * 
 */
UCLASS()
class ABYSSFPS_API UGA_Jump : public UAbyss_GameplayAbilityBase
{
	GENERATED_BODY()
	
	//------------------------------------------------------------------------------------------------------------------
public:
	UGA_Jump();
	
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
	
	
	// Called when character landed
	UFUNCTION()
	void OnLanded(const FHitResult& Hit);
	
	
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	
# pragma region Settings
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Jump")
	float JumpZVelocity = 600.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Jump")
	float AirControl = 0.35f;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Jump")
	int32 MaxJumpCount = 1;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Jump")
	float JumpCooldown = 0.1f;
	
	UPROPERTY(EditDefaultsOnly, Category = "---Abyss---|Jump")
	bool bCanJumpWhileCrouching = false;
	
	// Effects
	
# pragma endregion 
	
	// Current jump count
	int32 CurrentJumpCount = 0;
	
	
	void PerformJump();
	void PlayJumpEffects();
	void PlayLandEffects(const FHitResult& Hit);
	bool IsOnGround() const;
	void StartWaitingForLanding();
	
};
