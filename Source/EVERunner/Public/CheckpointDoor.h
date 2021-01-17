// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointDoor.generated.h"

DECLARE_DELEGATE(CheckpointReached)

class UBoxComponent;

UCLASS()
class EVERUNNER_API ACheckpointDoor : public AActor
{
	GENERATED_BODY()

	bool doorsAreClosing = false;

protected:
	void BeginPlay();

	UFUNCTION(BlueprintNativeEvent)
	void OpenDoor();
	virtual void OpenDoor_Implementation() {};

	UFUNCTION()
	void CallCheckpointReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* triggerBox;

	static constexpr float doorClosinTime = 5.f;
	static constexpr float closingDelayAfterPassingCheckpoint = 1.f;

public:
	ACheckpointDoor();

	FORCEINLINE const float GetDoorClosingTime() const { return doorClosinTime; }

	void StartClosingDoor();

	CheckpointReached CheckpointReachedDelegate;
};
