// Fill out your copyright notice in the Description page of Project Settings.


#include "Runner.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ARunner::ARunner()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Set player character mesh position
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -97.f), FRotator(0.f, -90.f, 0.f));

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 100.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 0.f;
	GetCharacterMovement()->MaxFlySpeed = 0.f;
	GetCharacterMovement()->AirControl = 0.f;
	GetCharacterMovement()->AirControlBoostMultiplier = 0.f;
	GetCharacterMovement()->AirControlBoostVelocityThreshold = 0.f;

	GetCharacterMovement()->SetPlaneConstraintEnabled(true);
	GetCharacterMovement()->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
}

void ARunner::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass, TEXT("user widget"));
	widget->AddToViewport();
	characterWidget = Cast<UCharacterWidget>(widget);
	characterWidget->UpdateStamina(GetStaminaPercent());
}

void ARunner::LooseStamina(float ammountLost)
{
	stamina = (stamina > ammountLost) ? stamina - ammountLost : 0;
	characterWidget->UpdateStamina(GetStaminaPercent());
}

void ARunner::GainStamina(float ammountRecovered)
{
	float tmpStamina = stamina + ammountRecovered;
	stamina = (tmpStamina > maxStaminaAmmount) ? maxStaminaAmmount : tmpStamina;
	characterWidget->UpdateStamina(GetStaminaPercent());
}

