// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/EngineTypes.h"
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
	virtual float GetStamina() const = 0;
	virtual void LooseStamina(float ammount) = 0;
	virtual void GainStamina(float ammount) = 0;
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

	static constexpr float staminaDrainRatePerTick = 2;
	static constexpr float staminaDrainTickTime = .1f;

	float axisXValue;
	bool isJumpPressed;
	bool isSprintPressed;
	bool isCrouchPressed;
	
	FTimerHandle sprintTimerHandle;

	void TickStaminaDrain();

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

public:
	UFUNCTION(BlueprintCallable)
	float GetXAxisValue() const { return axisXValue; }
	UFUNCTION(BlueprintCallable)
	bool GetIsJumpPressed() const { return isJumpPressed; }
	UFUNCTION(BlueprintCallable)
	bool GetIsSprintPressed() const { return isSprintPressed; }
	UFUNCTION(BlueprintCallable)
	bool GetIsCrouchPressed() const { return isCrouchPressed; }
};
