// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameHUDWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class HOMEWORK8_API UGameHUDWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;


	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXP_ProgressBar;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelTextbox;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ElapsedTimerTextbox;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StageTextbox;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldTextbox;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillCountTextbox;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EmenyLeftTextbox;
	
public:
	UFUNCTION()
	void UpdateExpBar(int32 CurrentExp, int32 MaxExp, int32 Level);
	UFUNCTION()
	void UpdateLevelText(int32 CurrentPlayerLevel);
	UFUNCTION()
	void UpdateStageText(int32 CurrentStageIndex);
	UFUNCTION()
	void UpdateTimerText();
	UFUNCTION()
	void UpdateGoldText(int32 CurrentLevel);
	UFUNCTION()
	void UpdateKillCountText(int32 CurrentLevel);
private:
	FTimerHandle UpdateTimeHandle;
};
