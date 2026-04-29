// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class UBoxComponent;
class AAiRtanny;

UCLASS()
class HOMEWORK8_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAiRtanny> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnInterval = .5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnDistance = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxEnemyCount = 100;



	UFUNCTION(BlueprintCallable)
	void StartSpawning();

	UFUNCTION(BlueprintCallable)
	void StopSpawning();
	
private:
	bool bSpawning = false;
	float LastSpawnTime = -999.f;
	
	UPROPERTY()
	AActor* TargetPlayer;

	void SpawnEnemy();
	FVector GetRandomSpawnLocation() const;
	int32 GetCurrentEnemyCount() const;

};
