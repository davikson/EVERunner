// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RootMotionController.h"
#include "Runner.generated.h"


UCLASS()
class ARunner : public ACharacter, public IRootMotionCharacterInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARunner();

protected:
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	static constexpr float maxStaminaAmmount = 100;
	float stamina = 0;

public:
	virtual float GetStamina() override { return stamina; }
	virtual void LooseStamina(float ammount) override;

};
