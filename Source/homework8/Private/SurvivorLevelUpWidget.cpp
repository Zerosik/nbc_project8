// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorLevelUpWidget.h"
#include "UpgradeDataAsset.h"
#include "SurvivorUpgradeChoiceWidget.h"
#include "Components/HorizontalBox.h"

void USurvivorLevelUpWidget::SetupChoices(const TArray<UUpgradeDataAsset*>& UpgradeChoices)
{
    if (!ChoiceBox || !ChoiceWidgetClass)
    {
        return;
    }

    ChoiceBox->ClearChildren();

    for (UUpgradeDataAsset* UpgradeData : UpgradeChoices)
    {
        if (!UpgradeData)
        {
            continue;
        }

        USurvivorUpgradeChoiceWidget* ChoiceWidget = CreateWidget<USurvivorUpgradeChoiceWidget>(
            GetOwningPlayer(),
            ChoiceWidgetClass
        );

        if (!ChoiceWidget)
        {
            continue;
        }

        ChoiceWidget->Setup(UpgradeData);
        ChoiceBox->AddChild(ChoiceWidget);
    }
}