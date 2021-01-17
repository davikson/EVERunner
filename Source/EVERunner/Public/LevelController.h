// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelWidget.h"
#include "Engine/EngineTypes.h"
#include "LevelController.generated.h"

class UWidgetComponent;
class ACheckpointDoor;

USTRUCT(BlueprintType)
struct FCheckpointAndTime
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	ACheckpointDoor* checkpoint;
	UPROPERTY(EditAnywhere)
	float targetTime;
};

UCLASS()
class EVERUNNER_API ALevelController : public AActor
{
	GENERATED_BODY()

	void UpdateCheckpointVariables();

	float timeElapsed;
	float targetTime;
	float doorClosingTime;
	static constexpr float timeIncrement = .1f;
	FTimerHandle timerHandle;
	int activeCheckpoint;

	UPROPERTY(EditDefaultsOnly, Category = "Params|Widgets")
	TSubclassOf<ULevelWidget> widgetClass = ULevelWidget::StaticClass();
	ULevelWidget* levelWidget;
	
public:	
	ALevelController();

protected:
	virtual void BeginPlay() override;

	void UpdateTime();

	FORCEINLINE const float GetTimeRemaining() const { return targetTime - timeElapsed; }

	void NextCheckpoint();

	UPROPERTY(EditInstanceOnly, Category="Params")
	TArray<FCheckpointAndTime> checkpoints;
};
