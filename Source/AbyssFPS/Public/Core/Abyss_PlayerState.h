// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"


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
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	
	//------------------------------------------------------------------------------------------------------------------
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "---Abyss---|Abilities")
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
	
	UPROPERTY()
	UAbyss_AttributeSet* AttributeSet = nullptr;
};
