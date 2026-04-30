// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorUpgradeChoiceWidget.h"
#include "UpgradeDataAsset.h"
#include "SurvivorGameMode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
void USurvivorUpgradeChoiceWidget::Setup(UUpgradeDataAsset* InUpgradeData)
{
    UpgradeData = InUpgradeData;

    if (!UpgradeData)
    {
        return;
    }

    if (NameText)
    {
        NameText->SetText(UpgradeData->DisplayName);
    }

    if (DescriptionText)
    {
        DescriptionText->SetText(UpgradeData->Description);
    }
}

void USurvivorUpgradeChoiceWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (SelectButton)
    {
        SelectButton->OnClicked.AddDynamic(this, &USurvivorUpgradeChoiceWidget::OnClicked);
    }
}

void USurvivorUpgradeChoiceWidget::OnClicked()
{
    if (!UpgradeData)
    {
        return;
    }

    ASurvivorGameMode* GM = Cast<ASurvivorGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GM)
    {
        return;
    }

    GM->SelectUpgrade(UpgradeData);
}
