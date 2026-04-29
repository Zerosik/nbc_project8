// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

UCLASS()
class HOMEWORK8_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta=(BindWidget))
    UButton* StartButton;

    UPROPERTY(meta=(BindWidget))
    UButton* QuitButton;
private:
    UFUNCTION()
    void OnStartClicked();

    UFUNCTION()
    void OnQuitClicked();
};
