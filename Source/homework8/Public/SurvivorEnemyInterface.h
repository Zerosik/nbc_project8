// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SurvivorEnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USurvivorEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HOMEWORK8_API ISurvivorEnemyInterface
{
	GENERATED_BODY()
public:
	UFUNCTION()
	virtual void HandleDeath()=0;

	UFUNCTION()
	virtual void OnPlayerOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	)=0;
};
