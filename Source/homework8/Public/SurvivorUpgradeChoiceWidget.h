// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivorUpgradeChoiceWidget.generated.h"

class UUpgradeDataAsset;
class UButton;
class UTextBlock;


UCLASS()
class HOMEWORK8_API USurvivorUpgradeChoiceWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable)
    void Setup(UUpgradeDataAsset* InUpgradeData);

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta=(BindWidget))
    UButton* SelectButton;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* NameText;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* DescriptionText;

private:
    UPROPERTY()
    UUpgradeDataAsset* UpgradeData;

    UFUNCTION()
    void OnClicked();
};
