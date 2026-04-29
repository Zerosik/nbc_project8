// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "ExperienceComponent.h"
#include "HealthComponent.h"
#include "homework8/homework8Character.h"

USurvivorGameInstance::USurvivorGameInstance()
{

}

void USurvivorGameInstance::SetPrevPlayerStatus()
{
	Ahomework8Character* Character = Cast<Ahomework8Character>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Character) {

		PrevPlayerStatus.Level = Character->ExperienceComponent->CurrentLevel;
		PrevPlayerStatus.CurrentExp = Character->ExperienceComponent->CurrentExp;
		PrevPlayerStatus.RequiredExp = Character->ExperienceComponent->RequiredExp;
		PrevPlayerStatus.CurrentHealth = Character->HealthComponent->CurrentHealth;
	}
}

FPlayerRunStatus USurvivorGameInstance::GetPrevPlayerStatus()
{
	return PrevPlayerStatus;
}

void USurvivorGameInstance::StartNewRun()
{
	LastRunResult = FSurvivorRunResult();
	CurrentStageIndex = 0;
	PrevPlayerStatus = FPlayerRunStatus();

	//기본값, BP에서 설정
	if (StageLevelNames.Num() == 0)
	{
		StageLevelNames.Add(TEXT("Level1"));
		StageLevelNames.Add(TEXT("Level2"));
		StageLevelNames.Add(TEXT("Level3"));
	}
}

FName USurvivorGameInstance::GetCurrentStageName() const
{
	if (StageLevelNames.IsValidIndex(CurrentStageIndex)) {
		return StageLevelNames[CurrentStageIndex];
	}
	//NAME_None은 반환값이 FName일떄 "빈값" 즉 False 처럼 사용가능
	return NAME_None;
}

bool USurvivorGameInstance::HasNextStage() const
{
	//다음 스테이지가 있는지?
	return StageLevelNames.IsValidIndex(CurrentStageIndex + 1);
}

FName USurvivorGameInstance::MoveToNextStageAndGetLevelName()
{

	if (HasNextStage()) {
		CurrentStageIndex++;
		return GetCurrentStageName();

	}
	return NAME_None;
}

void USurvivorGameInstance::AddStageResult(float SurvivalTime, int32 KillCount, int32 PlayerLevel)
{
	LastRunResult.SurvivalTime += SurvivalTime;
	LastRunResult.KillCount += KillCount;
	LastRunResult.PlayerLevel = PlayerLevel;


	//LastRunResult.ClearedStageCount = FMath::Max(
	//	LastRunResult.ClearedStageCount,
	//	CurrentStageIndex + 1
	//);
}

void USurvivorGameInstance::SetRunVictory(bool bVictory)
{
	LastRunResult.bVictory = bVictory;
	LastRunResult.ClearedStageCount = FMath::Max(
		LastRunResult.ClearedStageCount,
		CurrentStageIndex + 1
	);
}

void USurvivorGameInstance::ClearLastRunResult()
{
	LastRunResult = FSurvivorRunResult();
	CurrentStageIndex = 0;
}

int32 USurvivorGameInstance::GetCurrentStageNumber() const
{
	//UI용?
	return CurrentStageIndex + 1;
}

int32 USurvivorGameInstance::GetTotalStageCount() const
{
	return StageLevelNames.Num();
}
