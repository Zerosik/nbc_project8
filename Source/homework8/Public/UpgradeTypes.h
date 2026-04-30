// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UpgradeTypes.generated.h"

UENUM(BlueprintType)
enum class EUpgradeTargetType : uint8
{
    WeaponStat      UMETA(DisplayName = "Weapon Stat"),
    CharacterStat   UMETA(DisplayName = "Character Stat"),
    AddWeapon       UMETA(DisplayName = "Add Weapon"),
    UpgradeWeapon   UMETA(DisplayName = "Upgrade Weapon")
};

UENUM(BlueprintType)
enum class EWeaponUpgradeStat : uint8
{
    Damage              UMETA(DisplayName = "Damage"),
    AttackCooldown      UMETA(DisplayName = "Attack Cooldown"),
    MultiShotCount      UMETA(DisplayName = "Multi Shot Count"),
    PierceCount         UMETA(DisplayName = "Pierce Count")
};

UENUM(BlueprintType)
enum class EUpgradeValueType : uint8
{
    Add         UMETA(DisplayName = "Add"),
    Multiply    UMETA(DisplayName = "Multiply"),
    Set         UMETA(DisplayName = "Set")
};