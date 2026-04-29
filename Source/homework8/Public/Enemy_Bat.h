// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivorEnemyBase.h"
#include "Enemy_Bat.generated.h"

UCLASS()
class HOMEWORK8_API AEnemy_Bat : public ASurvivorEnemyBase
{
	GENERATED_BODY()
public:
	AEnemy_Bat();
	
	virtual void Tick(float DeltaSeconds) override;


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	FVector direction;

	void MoveToDirection(float DeltaTime);

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
