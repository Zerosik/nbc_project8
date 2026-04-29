// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SurvivorGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FSurvivorRunResult
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    bool bVictory = false;

    UPROPERTY(BlueprintReadOnly)
    float SurvivalTime = 0.0f;

    UPROPERTY(BlueprintReadOnly)
    int32 KillCount = 0;
    
    UPROPERTY(BlueprintReadOnly)
    int32 PlayerLevel = 1;

    UPROPERTY(BlueprintReadOnly)
    int32 ClearedStageCount = 0;
};

UCLASS()
class HOMEWORK8_API USurvivorGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	USurvivorGameInstance();

    UPROPERTY(BlueprintReadOnly)
	int32 TotalGold; //영구적 업그레이드에 사용

    UPROPERTY(BlueprintReadOnly)
    FSurvivorRunResult LastRunResult; //기록

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<FName> StageLevelNames; //Level 기록

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentStageIndex = 0;

    UFUNCTION(BlueprintCallable)
    void StartNewRun(); //result 초기화 및 처음부터

    UFUNCTION(BlueprintCallable)
    FName GetCurrentStageName() const;

    UFUNCTION(BlueprintCallable)
    bool HasNextStage() const;

    UFUNCTION(BlueprintCallable)
    FName MoveToNextStageAndGetLevelName();
    
    UFUNCTION(BlueprintCallable)
    void AddStageResult(float SurvivalTime, int32 KillCount, int32 PlayerLevel);


    UFUNCTION(BlueprintCallable)
    void SetRunVictory(bool bVictory);

    UFUNCTION(BlueprintCallable)
    void ClearLastRunResult();

    UFUNCTION(BlueprintCallable)
    int32 GetCurrentStageNumber() const;

    UFUNCTION(BlueprintCallable)
    int32 GetTotalStageCount() const;
};
