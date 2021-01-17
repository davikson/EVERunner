// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RootMotionController.h"
#include "CharacterWidget.h"
#include "Runner.generated.h"


UCLASS()
class ARunner : public ACharacter, public IRootMotionCharacterInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Params|Widgets")
	TSubclassOf<UCharacterWidget> widgetClass = UCharacterWidget::StaticClass();
	UCharacterWidget* characterWidget;

public:
	// Sets default values for this character's properties
	ARunner();

	virtual float GetStamina() const override { return stamina; }
	virtual void LooseStamina(float ammount) override;
	virtual void GainStamina(float ammount) override;

protected:
	virtual void BeginPlay() override;

	FORCEINLINE const float GetStaminaPercent() const { return stamina / maxStaminaAmmount; }

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	static constexpr float maxStaminaAmmount = 100;
	float stamina = 0;
};
