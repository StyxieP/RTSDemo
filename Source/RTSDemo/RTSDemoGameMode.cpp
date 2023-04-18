// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSDemoGameMode.h"
#include "RTSDemoPlayerController.h"
#include "RTSDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARTSDemoGameMode::ARTSDemoGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSDemoPlayerController::StaticClass();
	
	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		DefaultPawnClass = ABaseCharacter::StaticClass();
	}

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Script/RTSDemo.RTSDemoCharacter"));
	//if (PlayerPawnBPClass.Class != nullptr)
	//{
		//DefaultPawnClass = ARTSDemoCharacter::StaticClass(); //PlayerPawnBPClass.Class;
	//}
}