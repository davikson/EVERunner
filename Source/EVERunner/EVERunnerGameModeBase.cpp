// Copyright Epic Games, Inc. All Rights Reserved.


#include "RootMotionController.h"
#include "EVERunnerGameModeBase.h"

AEVERunnerGameModeBase::AEVERunnerGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Runner_BP"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	PlayerControllerClass = ARootMotionController::StaticClass();
}
