// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "UpgradeTypes.h"

#include "UpgradeDataAsset.generated.h"



UCLASS(BlueprintType)
class HOMEWORK8_API UUpgradeDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName UpgradeID;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(MultiLine=true))
    FText Description;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EUpgradeTargetType TargetType = EUpgradeTargetType::WeaponStat;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EWeaponUpgradeStat WeaponStat = EWeaponUpgradeStat::Damage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    EUpgradeValueType ValueType = EUpgradeValueType::Add;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Value = 0.0f;

    // 추후 특정 무기만 강화할 때 사용
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName TargetWeaponID = NAME_None;

    // 같은 업그레이드가 여러 번 나와도 되는지
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bRepeatable = true;

    // 선택지 등장 최소 레벨
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    int32 RequiredPlayerLevel = 1;
};