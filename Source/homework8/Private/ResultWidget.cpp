// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultWidget.h"
#include "SurvivorPlayerController.h"
#include "SurvivorGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"




void UResultWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (MainMenuButton)
    {
        MainMenuButton->OnClicked.AddDynamic(this, &UResultWidget::OnMainMenuClicked);
    }
}

void UResultWidget::SetupResult(bool bVictory)
{
    bCachedVictory = bVictory;

    if (ResultText) {
        ResultText->SetText(bVictory ? FText::FromString(TEXT("CLEAR")) : FText::FromString(TEXT("Game Over")));
    }

    USurvivorGameInstance* SGI = Cast<USurvivorGameInstance>(GetGameInstance());
    if (!SGI)
        return;

    const FSurvivorRunResult& Result = SGI->LastRunResult;

    if (StageText) {
        StageText->SetText(FText::FromString(
            FString::Printf(TEXT("Stage cleared : %d"), Result.ClearedStageCount)
        ));
    }

    if (SurvivalTimeText) {
        const int32 Minutes = FMath::FloorToInt(Result.SurvivalTime / 60.f);
        const int32 Seconds = FMath::FloorToInt(FMath::Fmod(Result.SurvivalTime, 60.0f));

        SurvivalTimeText->SetText(FText::FromString(
            FString::Printf(TEXT("Survivor Time : %02d : %02d"), Minutes, Seconds)
        ));
    }

    if (KillCountText) {
        KillCountText->SetText(FText::FromString(
            FString::Printf(TEXT("Total Kills : %d"), Result.KillCount)
        ));
    }

    if (LevelText) {
        LevelText->SetText(FText::FromString(
            FString::Printf(TEXT("Level: %d"), Result.PlayerLevel)
        ));
    }

}

void UResultWidget::OnMainMenuClicked()
{
    if (ASurvivorPlayerController* SPC = Cast<ASurvivorPlayerController>(GetOwningPlayer())) {
        SPC->ReturnToMainMenu();
    }
}
