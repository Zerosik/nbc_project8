// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorLevelUpWidget.generated.h"

class UUpgradeDataAsset;
class UHorizontalBox;
class USurvivorUpgradeChoiceWidget;

UCLASS()
class HOMEWORK8_API USurvivorLevelUpWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void SetupChoices(const TArray<UUpgradeDataAsset*>& UpgradeChoices);

protected:
    UPROPERTY(meta=(BindWidget))
    UHorizontalBox* ChoiceBox;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<USurvivorUpgradeChoiceWidget> ChoiceWidgetClass;
};
