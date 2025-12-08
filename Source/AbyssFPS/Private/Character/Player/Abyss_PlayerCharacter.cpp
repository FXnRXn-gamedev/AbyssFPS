// © 2025 FXnRXn. AbyssFPS — Development Build. All rights reserved


#include "AbyssFPS/Public/Character/Player/Abyss_PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// =====================================================================================================================
// ---> CONSTRUCTOR & UNREAL CALLBACK <---
// =====================================================================================================================

AAbyss_PlayerCharacter::AAbyss_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Configure capsule
	GetCapsuleComponent()->InitCapsuleSize(34.f, 92.f);
	
	// Setup Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(25.f, 0.f, 64.f));
	CameraComponent->bUsePawnControlRotation = true;
	
	//--> NOT NEEDED : Configure mesh for third person
	//GetMesh()->SetOwnerNoSee(true);
	
	
	// Setup Movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bUseControllerRotationYaw = true;
	
	
	
	// Replication
	SetReplicates(true);
	SetReplicateMovement(true);
}

void AAbyss_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Set default FOV
	if (CameraComponent) CameraComponent->SetFieldOfView(DefaultFOV);
}


// =====================================================================================================================
// ---> LOCOMOTION HANDLING <---
// =====================================================================================================================

void AAbyss_PlayerCharacter::HandleMoveInput(const FVector2D& MoveInput)
{
	if (Controller && MoveInput.SizeSquared() > 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MoveInput.Y);
		AddMovementInput(RightDirection, MoveInput.X);
	}
}

void AAbyss_PlayerCharacter::HandleLookInput(const FVector2D& LookInput)
{
	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}