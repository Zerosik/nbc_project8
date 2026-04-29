// Fill out your copyright notice in the Description page of Project Settings.


#include "MainManuGameMode.h"
#include "MainMenuPlayerController.h"

AMainManuGameMode::AMainManuGameMode()
{
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();

	DefaultPawnClass = nullptr;
}
