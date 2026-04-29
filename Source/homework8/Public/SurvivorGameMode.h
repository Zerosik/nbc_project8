// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SurvivorGameMode.generated.h"

class AEnemySpawner;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageChanged, int32, NewLevelIndex);

UCLASS()
class HOMEWORK8_API ASurvivorGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ASurvivorGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf< AEnemySpawner> SpawnerClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ClearTime = 30.f;

    UFUNCTION(BlueprintCallable)
    void StartRun();

    UFUNCTION(BlueprintCallable)
    void EndRun(bool bVictory);

    UPROPERTY(BlueprintAssignable)
    FOnStageChanged OnStageChanged;
private:
    UPROPERTY()
    class AEnemySpawner* EnemySpawner;

    bool bRunEnded = false;

    void CreateSpawnerIfNeeded();

    //승패결정
    void HandleStageClear();
    void HandlePlayerDead();

    void SaveResultToGameInstance(bool bStageCleared);
    void ShowFinalResult(bool bVictory);
    void OpenNextStage();
};
