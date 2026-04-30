// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class ASurvivorEnemyBase;
class UBoxComponent;
//class AAiRtanny;

UENUM(BlueprintType)
enum class EVSWaveSpawnShape : uint8
{
    CircleAroundPlayer UMETA(DisplayName = "Circle Around Player"),
    LineFromRandomSide UMETA(DisplayName = "Line From Random Side")
};

USTRUCT(BlueprintType)
struct FVSWaveSpawnEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float TriggerTime = 20.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TSubclassOf<ASurvivorEnemyBase> EnemyClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 SpawnCount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float SpawnDistance = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float SpawnSpacing = 80.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    EVSWaveSpawnShape SpawnShape = EVSWaveSpawnShape::CircleAroundPlayer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bTriggered = false;
};

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
	TSubclassOf<ASurvivorEnemyBase> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnInterval = .5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnDistance = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxEnemyCount = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float EnemyHealthScale = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave Events")
    TArray<FVSWaveSpawnEvent> WaveEvents;

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

	//Wave
	void CheckWaveEvents();
	void TriggerWaveEvent(FVSWaveSpawnEvent& WaveEvent);

	void SpawnCircleWave(const FVSWaveSpawnEvent& WaveEvent);
	void SpawnLineWave(const FVSWaveSpawnEvent& WaveEvent);

	FVector GetRandomDirection2D() const;

};
