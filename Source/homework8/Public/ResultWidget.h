// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class HOMEWORK8_API UResultWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void SetupResult(bool bVictory);

protected:
    virtual void NativeConstruct() override;
    
    UPROPERTY(meta=(BindWidget))
    UTextBlock* ResultText;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* StageText;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* SurvivalTimeText;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* KillCountText;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* LevelText;

    UPROPERTY(meta=(BindWidget))
    UButton* MainMenuButton;

private:
    UFUNCTION()
    void OnMainMenuClicked();

    bool bCachedVictory = false;
};
