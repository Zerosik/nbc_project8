// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeManager.generated.h"

class UUpgradeDataAsset;
class Ahomework8Character;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOMEWORK8_API UUpgradeManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UUpgradeManager();

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TArray<UUpgradeDataAsset*> UpgradePool;

    UFUNCTION(BlueprintCallable)
    TArray<UUpgradeDataAsset*> GenerateUpgradeChoices(int32 ChoiceCount, int32 PlayerLevel) const;

    UFUNCTION(BlueprintCallable)
    void ApplyUpgrade(UUpgradeDataAsset* UpgradeData, Ahomework8Character* Player);

private:
    bool IsUpgradeAvailable(UUpgradeDataAsset* UpgradeData, int32 PlayerLevel) const;
};