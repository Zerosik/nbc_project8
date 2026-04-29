// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "AiRtanny.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bSpawning || !TargetPlayer || !EnemyClass || !GetWorld())
		return;
	//최대소환수 제한
	if (GetCurrentEnemyCount() >= MaxEnemyCount)
		return;

	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastSpawnTime >= SpawnInterval) {
		SpawnEnemy();
		LastSpawnTime = CurrentTime;
	}
}

void AEnemySpawner::StartSpawning()
{
	bSpawning = true;
}

void AEnemySpawner::StopSpawning()
{
	bSpawning = false;
}

void AEnemySpawner::SpawnEnemy()
{
	const FVector SpawnLocation = GetRandomSpawnLocation();

	AAiRtanny* SpawnedActor = GetWorld()->SpawnActor<AAiRtanny>(
		EnemyClass,
		SpawnLocation,
		FRotator::ZeroRotator
	);
	//가끔 nullptr
	if (SpawnedActor) {
		//기본 컨트롤러 미할당 시 움직이지 않음
		SpawnedActor->SpawnDefaultController();
	}
}

FVector AEnemySpawner::GetRandomSpawnLocation() const
{
	if (!TargetPlayer)
		return GetActorLocation();

	const float Angle = FMath::RandRange(0.f, 360.f);
	//랜덤 각도를 Cos, Sin 을 이용해 플레이어 중심 단위방향벡터로 변경
	const FVector Direction = FVector(
		FMath::Cos(FMath::DegreesToRadians((Angle))),
		FMath::Sin(FMath::DegreesToRadians((Angle))),
		0.f
	);
	//플레이어 중심으로 SpawnDistance거리의 랜덤위치 
	return TargetPlayer->GetActorLocation() + Direction * SpawnDistance;
}

int32 AEnemySpawner::GetCurrentEnemyCount() const
{
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAiRtanny::StaticClass(), Enemies);
	return Enemies.Num();
}

