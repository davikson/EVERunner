// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelWidget.generated.h"

class ALevelController;
/**
 * 
 */
UCLASS()
class EVERUNNER_API ULevelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	ALevelController* levelControllerPtr;

public:
	void SetLevelControllerPtr(ALevelController* ptr) { levelControllerPtr = ptr; }

	UFUNCTION(BlueprintNativeEvent, Category=LevelWidget)
	void UpdateTimeRemaining(float timeRemaining);
	virtual void UpdateTimeRemaining_Implementation(float timeRemaining) {}
};