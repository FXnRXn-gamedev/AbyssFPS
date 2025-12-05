// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "Character/Player/Abyss_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"





// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================


AAbyss_PlayerController::AAbyss_PlayerController()
{
	bReplicates = true;
}

void AAbyss_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// Add input mapping context
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultAbyssMappingContext)
		{
			EnhancedInputSubsystem->AddMappingContext(DefaultAbyssMappingContext, 0);
		}
	}
}

void AAbyss_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) return;

	if (MoveAction) EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	if (LookAction) EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	
}


// =====================================================================================================================
// ---> NET <---
// =====================================================================================================================

void AAbyss_PlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}








// =====================================================================================================================
// ---> INPUT <---
// =====================================================================================================================

void AAbyss_PlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
}

void AAbyss_PlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
}
