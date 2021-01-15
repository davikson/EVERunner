// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerManager.h"
#include "RootMotionController.h"

void ARootMotionController::BeginPlay()
{
	Super::BeginPlay();
	pawnReference = GetPawn();
	characterReference = Cast<IRootMotionCharacterInterface>(pawnReference);
	if (!characterReference)
		UE_LOG(LogTemp, Error, TEXT("Pawn doesn't implement IRootMotionCharacterInterface"));
}

void ARootMotionController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveRight", this, &ARootMotionController::MoveRight);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ARootMotionController::JumpPressed);
	InputComponent->BindAction("Jump", IE_Released, this, &ARootMotionController::JumpReleased);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &ARootMotionController::SprintPressed);
	InputComponent->BindAction("Sprint", IE_Released, this, &ARootMotionController::SprintReleased);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &ARootMotionController::CrouchPressed);
	InputComponent->BindAction("Crouch", IE_Released, this, &ARootMotionController::CrouchReleased);
}

void ARootMotionController::MoveRight(float value)
{
	axisXValue = value;
	pawnReference->AddMovementInput(FVector::LeftVector, FMath::Sign(value));
}
void ARootMotionController::JumpPressed()
{
	isJumpPressed = true;
}
void ARootMotionController::JumpReleased()
{
	isJumpPressed = false;
}
void ARootMotionController::SprintPressed()
{
	if (characterReference->GetStamina() > 0.f)
	{
		isSprintPressed = true;
		GetWorldTimerManager().SetTimer(sprintTimerHandle, this, &ARootMotionController::TickStaminaDrain, staminaDrainTickTime, true);
	}
}
void ARootMotionController::SprintReleased()
{
	isSprintPressed = false;
	GetWorldTimerManager().ClearTimer(sprintTimerHandle);
}
void ARootMotionController::CrouchPressed()
{
	isCrouchPressed = true;
}
void ARootMotionController::CrouchReleased()
{
	isCrouchPressed = false;
}

void ARootMotionController::TickStaminaDrain()
{
	characterReference->LooseStamina(staminaDrainRatePerTick);
	if (characterReference->GetStamina() <= 0)
	{
		SprintReleased();
	}
}
