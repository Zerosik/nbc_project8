// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

class APotionItem;

UCLASS()
class HOMEWORK8_API AItemSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSpawner();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<APotionItem> ItemClass; //포션아이템 넣지만 강의때처럼 데이터테이블이나 데이터에셋사용하도록 나중에 바꾸기

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BaseItemSpawnChance = 0.02f; //생성시도시 생성확률
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnTryInterval = 0.05f; //초마다 스폰 시도함
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnMinDistanceFromPlayer = 1000.f; //스폰 최소거리
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnMaxDistanceFromPlayer = 2000.f; //스폰 최대거리


	UFUNCTION(BlueprintCallable)
	void StartSpawning();

	UFUNCTION(BlueprintCallable)
	void StopSpawning();

private:
	bool bSpawning = false;
	float LastSpawnTime = -999.f;

	UPROPERTY()
	AActor* TargetPlayer;
	
	void TrySpawnItem();
	void SpawnItem();

	FVector GetRandomSpawnLocationInRange() const;
};
