// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class EVERUNNER_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = LevelWidget)
	void UpdateStamina(float stamina);
	virtual void UpdateStamina_Implementation(float stamina) {}
};
