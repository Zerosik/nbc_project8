// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SurvivorGameMode.generated.h"

class AEnemySpawner;
class Ahomework8Character;
class UUpgradeDataAsset;
class UUpgradeManager;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageChanged, int32, NewLevelIndex);

UCLASS()
class HOMEWORK8_API ASurvivorGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ASurvivorGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UUpgradeManager* UpgradeManager;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf< AEnemySpawner> SpawnerClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float ClearTime = 30.f;
    
    UFUNCTION(BlueprintCallable)
    void OnPlayerLevelUp(int32 NewLevel);

    UFUNCTION(BlueprintCallable)
    void SelectUpgrade(UUpgradeDataAsset* SelectedUpgrade);

    UFUNCTION(BlueprintCallable)
    void StartRun();

    UFUNCTION(BlueprintCallable)
    void EndRun(bool bVictory);

    UPROPERTY(BlueprintAssignable)
    FOnStageChanged OnStageChanged;

private:
    UPROPERTY()
    class AEnemySpawner* EnemySpawner;
    UPROPERTY()
    Ahomework8Character* CachedPlayer;

    UPROPERTY()
    TArray<UUpgradeDataAsset*> CurrentUpgradeChoices;
    bool bRunEnded = false;

    void BindPlayerEvents();

    void CreateSpawnerIfNeeded();

    //승패결정
    void HandleStageClear();
    void HandlePlayerDead();

    void SaveResultToGameInstance(bool bStageCleared);
    void ShowFinalResult(bool bVictory);
    void OpenNextStage();
};
