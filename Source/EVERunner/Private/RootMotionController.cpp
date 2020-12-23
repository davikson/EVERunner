// Fill out your copyright notice in the Description page of Project Settings.


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
	pawnReference->AddMovementInput(FVector::RightVector, FMath::Sign(value));
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
	isSprintPressed = true;
}
void ARootMotionController::SprintReleased()
{
	isSprintPressed = false;
}
void ARootMotionController::CrouchPressed()
{
	isCrouchPressed = true;
}
void ARootMotionController::CrouchReleased()
{
	isCrouchPressed = false;
}
