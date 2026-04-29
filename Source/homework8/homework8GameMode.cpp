// Copyright Epic Games, Inc. All Rights Reserved.

#include "homework8GameMode.h"
#include "homework8PlayerController.h"
#include "homework8Character.h"
#include "UObject/ConstructorHelpers.h"
#include "SurvivorPlayerController.h"

Ahomework8GameMode::Ahomework8GameMode()
{
	// use our custom PlayerController class
	//PlayerControllerClass = Ahomework8PlayerController::StaticClass();
	PlayerControllerClass = ASurvivorPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	//static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	//if(PlayerControllerBPClass.Class != NULL)
	//{
	//	PlayerControllerClass = PlayerControllerBPClass.Class;
	//}
}