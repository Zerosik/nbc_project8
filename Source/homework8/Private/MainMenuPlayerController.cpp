// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "MainMenuWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivorGameInstance.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}
void AMainMenuPlayerController::StartGame()
{
	USurvivorGameInstance* GI = Cast<USurvivorGameInstance>(GetGameInstance());
	if (!GI)
		return;
	//초기화를 한번 날려주고 시작.
	GI->StartNewRun();
	const FName FirstStageName = GI->GetCurrentStageName();
	if (FirstStageName == NAME_None)
		return;
	UGameplayStatics::OpenLevel(this, FirstStageName);
}
void AMainMenuPlayerController::QuitGame()
{
	UKismetSystemLibrary::QuitGame(
		this,
		this,
		EQuitPreference::Quit,
		false
	);
}