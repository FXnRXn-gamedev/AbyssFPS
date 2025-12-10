// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "Character/Player/Abyss_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Character/Player/Abyss_PlayerCharacter.h"
#include "Core/Abyss_PlayerState.h"


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

void AAbyss_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	CachedCharacter = Cast<AAbyss_PlayerCharacter>(InPawn);
	
	//Initialize ability system
	AAbyss_PlayerState* PS  = GetPlayerState<AAbyss_PlayerState>();
	if (PS && CachedCharacter) PS->InitializeAbilitySystem(CachedCharacter);
	
	
}

void AAbyss_PlayerController::OnUnPossess()
{
	CachedCharacter = nullptr;
	
	Super::OnUnPossess();
}

void AAbyss_PlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
	
	CachedCharacter = Cast<AAbyss_PlayerCharacter>(P);
	
	//Client-side ability system init
	AAbyss_PlayerState* PS  = GetPlayerState<AAbyss_PlayerState>();
	if (PS && CachedCharacter) PS->InitializeAbilitySystem(CachedCharacter);
}


// =====================================================================================================================
// ---> INPUT <---
// =====================================================================================================================



void AAbyss_PlayerController::Input_Move(const FInputActionValue& InputActionValue)
{
	if (!CachedCharacter) return;
	
	const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
	CachedCharacter->HandleMoveInput(MoveValue);
}

void AAbyss_PlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	if (!CachedCharacter) return;
	
	FVector2D LookValue = InputActionValue.Get<FVector2D>() * MouseSensitivity;
	if (bInvertYAxis) LookValue.Y *= -1.0f;
	CachedCharacter->HandleLookInput(LookValue);
}


// =====================================================================================================================
// ---> HELPER <---
// =====================================================================================================================



AAbyss_PlayerCharacter* AAbyss_PlayerController::GetTAbyssCharacter() const
{
	return CachedCharacter ? CachedCharacter : Cast<AAbyss_PlayerCharacter>(GetPawn());
}

UAbilitySystemComponent* AAbyss_PlayerController::GetAbilitySystemComponent() const
{
	// Return ability system component from possessed character
	AAbyss_PlayerState* PS = GetPlayerState<AAbyss_PlayerState>();
	return PS ? PS->GetAbilitySystemComponent() : nullptr;
}