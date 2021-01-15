// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointDoor.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"

ACheckpointDoor::ACheckpointDoor()
{
	triggrBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger box"));
	triggrBox->SetupAttachment(RootComponent);
}

void ACheckpointDoor::BeginPlay()
{
	Super::BeginPlay();
	triggrBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointDoor::CallCheckpointReached);
}

void ACheckpointDoor::StartClosingDoor()
{
	if (doorsAreClosing) return;
	doorsAreClosing = true;
	OpenDoor();
}

void ACheckpointDoor::CallCheckpointReached(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CheckpointReachedDelegate.IsBound())
	{
		CheckpointReachedDelegate.Execute();
		CheckpointReachedDelegate.Unbind();
	}
	FTimerHandle timerHandle;
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACheckpointDoor::StartClosingDoor, closingDelayAfterPassingCheckpoint);
}

