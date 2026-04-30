// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeManager.h"
#include "WeaponComponent.h"
#include "homework8/homework8Character.h"
#include "UpgradeDataAsset.h"
// Sets default values for this component's properties
UUpgradeManager::UUpgradeManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

TArray<UUpgradeDataAsset*> UUpgradeManager::GenerateUpgradeChoices(int32 ChoiceCount, int32 PlayerLevel) const
{
    TArray<UUpgradeDataAsset*> AvailableUpgrades;

    for (UUpgradeDataAsset* UpgradeData : UpgradePool)
    {
        if (IsUpgradeAvailable(UpgradeData, PlayerLevel))
        {
            AvailableUpgrades.Add(UpgradeData);
        }
    }

    TArray<UUpgradeDataAsset*> Result;

    while (Result.Num() < ChoiceCount && AvailableUpgrades.Num() > 0)
    {
        const int32 RandomIndex = FMath::RandRange(0, AvailableUpgrades.Num() - 1);

        Result.Add(AvailableUpgrades[RandomIndex]);
        AvailableUpgrades.RemoveAt(RandomIndex);
    }

    return Result;
}

void UUpgradeManager::ApplyUpgrade(UUpgradeDataAsset* UpgradeData, Ahomework8Character* Player)
{
    if (!UpgradeData || !Player)
    {
        return;
    }

    switch (UpgradeData->TargetType)
    {
    case EUpgradeTargetType::WeaponStat:
        if (Player->WeaponComponent)
        {
            Player->WeaponComponent->ApplyWeaponUpgrade(
                UpgradeData->WeaponStat,
                UpgradeData->ValueType,
                UpgradeData->Value
            );
        }
        break;

    case EUpgradeTargetType::CharacterStat:
        // 추후 StatComponent 추가 시 여기서 처리
        break;

    case EUpgradeTargetType::AddWeapon:
        // 추후 WeaponComponent에 AddWeapon() 추가 시 처리
        break;

    case EUpgradeTargetType::UpgradeWeapon:
        // 추후 특정 무기 ID 강화 처리
        break;

    default:
        break;
    }
}

bool UUpgradeManager::IsUpgradeAvailable(UUpgradeDataAsset* UpgradeData, int32 PlayerLevel) const
{
    if (!UpgradeData)
    {
        return false;
    }

    if (PlayerLevel < UpgradeData->RequiredPlayerLevel)
    {
        return false;
    }

    return true;
}
