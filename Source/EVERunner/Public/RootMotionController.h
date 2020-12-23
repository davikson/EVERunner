// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RootMotionController.generated.h"

UINTERFACE()
class URootMotionCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

class IRootMotionCharacterInterface
{
	GENERATED_BODY()
public:
};

/**
 * 
 */
UCLASS()
class EVERUNNER_API ARootMotionController : public APlayerController
{
	GENERATED_BODY()

	APawn* pawnReference;
	IRootMotionCharacterInterface* characterReference;

	float axisXValue;
	bool isJumpPressed;
	bool isSprintPressed;
	bool isCrouchPressed;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void MoveRight(float value);
	void JumpPressed();
	void JumpReleased();
	void SprintPressed();
	void SprintReleased();
	void CrouchPressed();
	void CrouchReleased();
};
