// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorRunState.generated.h"

UENUM(BlueprintType)
enum class ESurvivorRunState : uint8
{
    Waiting     UMETA(DisplayName = "Waiting"),
    Playing     UMETA(DisplayName = "Playing"),
    GameOver    UMETA(DisplayName = "GameOver"),
    Victory     UMETA(DisplayName = "Victory")
};