// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSDemoGameMode.h"
#include "RTSDemoPlayerController.h"
#include "RTSDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARTSDemoGameMode::ARTSDemoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSDemoPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}