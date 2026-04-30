// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivorPlayerController.generated.h"

class UUpgradeDataAsset;
class UInputMappingContext;
class UInputAction;
class UResultWidget;
class UGameHUDWidget;
class USurvivorLevelUpWidget;
struct FInputActionValue;

UCLASS()
class HOMEWORK8_API ASurvivorPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ASurvivorPlayerController();

#pragma region INPUTS
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* TopdownMoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ManualAttackAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseGameAction;
#pragma endregion INPUTS
#pragma region UI_Class
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelUPMenuWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> ResultWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
#pragma endregion UI_Class

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay();

	void OnMoveTriggered(const FInputActionValue& value);
	void OnMoveCompleted(const FInputActionValue& value);
	void OnManualAttackTriggered(const FInputActionValue& value);

public:
	UPROPERTY(EditAnywhere)
	FName MainMenuLevelName = TEXT("MenuLevel");

	//UI관련 Public
	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void ShowLevelUPWidget(const TArray<UUpgradeDataAsset*>& UpgradeChoices);
	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void CloseLevelUPWidget();

	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void TogglePauseWidget();
	
	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void ShowResultWidget(bool bVictory = false);
	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void CloseResultWidget();

	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void CloseGameHUD();

	void ReturnToMainMenu();
private:
	UFUNCTION(BlueprintCallable, Category = "UserInterface")
	void ClearUI();

	/*FTimerHandle UpdateElapsedTimeHandle;*/

#pragma region Widget
	UPROPERTY(VisibleAnywhere, Category = "UI")
	USurvivorLevelUpWidget* LevelUPMenuWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UUserWidget* PauseMenuWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UResultWidget* ResultWidgetInstance;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UUserWidget* GameHUDWidgetInstance;
#pragma endregion Widget
};
