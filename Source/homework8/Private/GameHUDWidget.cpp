// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUDWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "homework8/homework8Character.h"
#include "HealthComponent.h"
#include "ExperienceComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivorGameState.h"
#include "SurvivorGameMode.h"
#include "SurvivorGameInstance.h"
#include "TimerManager.h"


void UGameHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    Ahomework8Character* Player = Cast<Ahomework8Character>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!Player || !Player->ExperienceComponent)
        return;
    //Player.HealthComponent->OnHealthChanged.AddDynamic(this, &UGameHUDWidget::Update)
    Player->ExperienceComponent->OnExpChanged.AddDynamic(this, &UGameHUDWidget::UpdateExpBar);

    

    ASurvivorGameState* SGS = GetWorld()->GetGameState<ASurvivorGameState>();
    if (SGS) {
        SGS->OnKillCountChanged.AddDynamic(this, &UGameHUDWidget::UpdateKillCountText);
        
        GetWorld()->GetTimerManager().SetTimer(UpdateTimeHandle, this, &UGameHUDWidget::UpdateTimerText, 0.2f, true);
    }
    if (USurvivorGameInstance* GI = Cast<USurvivorGameInstance>(GetGameInstance())) {
        UpdateStageText(GI->GetCurrentStageNumber());
        UpdateExpBar(GI->PlayerExpLastStage, Player->ExperienceComponent->CalcRequiredExp(GI->PlayerLevelLastStage), GI->PlayerLevelLastStage);
    }
}

void UGameHUDWidget::UpdateExpBar(int32 CurrentExp, int32 RequiredExp, int32 Level)
{
    float ratio = static_cast<float>(CurrentExp) / RequiredExp;
    if(EXP_ProgressBar)
        EXP_ProgressBar->SetPercent(ratio);
    if(LevelTextbox)
        LevelTextbox->SetText(FText::FromString(FString::Printf(TEXT("LV : %d"), Level)));
}

void UGameHUDWidget::UpdateLevelText(int32 CurrentPlayerLevel)
{
    LevelTextbox->SetText(FText::FromString(FString::Printf(TEXT("LV %d"), CurrentPlayerLevel)));
}

void UGameHUDWidget::UpdateStageText(int32 CurrentStageIndex)
{
    StageTextbox->SetText(FText::FromString(FString::Printf(TEXT("Stage : %d"), CurrentStageIndex)));
}

void UGameHUDWidget::UpdateTimerText()
{
    ASurvivorGameState* SGS = GetWorld()->GetGameState<ASurvivorGameState>();

    const int32 Minutes = FMath::FloorToInt(SGS->SurvivedTime / 60.f);
    const int32 Seconds = FMath::FloorToInt(FMath::Fmod(SGS->SurvivedTime, 60.0f));
    ElapsedTimerTextbox->SetText(FText::FromString(FString::Printf(TEXT("%02d : %02d"), Minutes, Seconds)));
}

void UGameHUDWidget::UpdateGoldText(int32 CurrentGold)
{
    GoldTextbox->SetText(FText::FromString(FString::Printf(TEXT("GOLD : %d"), CurrentGold)));
}

void UGameHUDWidget::UpdateKillCountText(int32 CurrentKillCount)
{
    KillCountTextbox->SetText(FText::FromString(FString::Printf(TEXT("KILL : %d"), CurrentKillCount)));
}
