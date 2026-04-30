// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorEnemyBase.h"
#include "AiRtanny.generated.h"

UCLASS()
class HOMEWORK8_API AAiRtanny : public ASurvivorEnemyBase
{
	GENERATED_BODY()

public:
	AAiRtanny();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


private:
	UPROPERTY()
	AActor* TargetPlayer;
	
	void MoveToPlayer(float DeltaTime);

	void HandleDeath() override;

	void OnPlayerOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

};
