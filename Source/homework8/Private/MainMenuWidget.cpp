// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "MainMenuPlayerController.h"

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartClicked);
    }

    if (QuitButton)
    {
        QuitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitClicked);
    }
}

void UMainMenuWidget::OnStartClicked()
{
    if (AMainMenuPlayerController* PC = Cast<AMainMenuPlayerController>(GetOwningPlayer()))
    {
        PC->StartGame();
    }
}

void UMainMenuWidget::OnQuitClicked()
{
    if (AMainMenuPlayerController* PC = Cast<AMainMenuPlayerController>(GetOwningPlayer()))
    {
        PC->QuitGame();
    }
}