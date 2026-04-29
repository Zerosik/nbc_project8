// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MainMenuPlayerController.generated.h"

class UMainMenuWidget;

UCLASS()
class HOMEWORK8_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

    UFUNCTION(BlueprintCallable)
    void StartGame();

    UFUNCTION(BlueprintCallable)
    void QuitGame();
private:
    UPROPERTY()
    UMainMenuWidget* MainMenuWidget;
};
