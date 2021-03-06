// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetComponent.h"
#include "TimerManager.h"
#include "CheckpointDoor.h"
#include "LevelController.h"

ALevelController::ALevelController()
{
	timeElapsed = 0;
	targetTime = 0;
	doorClosingTime = 0;
	activeCheckpoint = 0;
}

void ALevelController::BeginPlay()
{
	Super::BeginPlay();
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), widgetClass, TEXT("level widget"));
	widget->AddToViewport();
	levelWidget = Cast<ULevelWidget>(widget);
	levelWidget->SetLevelControllerPtr(this);

	activeCheckpoint = 0;
	UpdateCheckpointVariables();
	GetWorldTimerManager().SetTimer(timerHandle, this, &ALevelController::UpdateTime, timeIncrement, true);
}

void ALevelController::UpdateTime()
{
	timeElapsed += timeIncrement;
	const float timeRemaining = GetTimeRemaining();
	levelWidget->UpdateTimeRemaining(timeRemaining);
	if (timeRemaining <= 0)
	{
		GetWorldTimerManager().ClearTimer(timerHandle);
		levelWidget->UpdateTimeRemaining(0);
		levelWidget->ShowGameOverScreen();
	}
	else if (timeRemaining <= doorClosingTime)
	{
		checkpoints[activeCheckpoint].checkpoint->StartClosingDoor();
	}
}

void ALevelController::UpdateCheckpointVariables()
{
	if (activeCheckpoint < checkpoints.Num())
	{
		targetTime = checkpoints[activeCheckpoint].targetTime + timeElapsed;
		doorClosingTime = checkpoints[activeCheckpoint].checkpoint->GetDoorClosingTime();
		checkpoints[activeCheckpoint].checkpoint->CheckpointReachedDelegate.BindUObject(this, &ALevelController::NextCheckpoint);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(timerHandle);
		levelWidget->ShowLevelFinishedScreen(timeElapsed);
	}
}

void ALevelController::NextCheckpoint()
{
	activeCheckpoint++;
	UpdateCheckpointVariables();
}

void ALevelController::PlayerKilled()
{
	bool playerKilled = true;
	levelWidget->ShowGameOverScreen(playerKilled);
	GetWorldTimerManager().ClearTimer(timerHandle);
}
