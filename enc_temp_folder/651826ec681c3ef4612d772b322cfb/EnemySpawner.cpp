// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "AiRtanny.h"
#include "HealthComponent.h"
#include "SurvivorGameState.h"
#include "Enemy_Bat.h"
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

	CheckWaveEvents();
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
	//가끔 nullptr 강제스폰방법확인
	if (SpawnedActor) {
		Enemies.Add(SpawnedActor);
		SpawnedActor->MySpawner = this;
		SpawnedActor->HealthComponent->SetMaxHealth(SpawnedActor->HealthComponent->MaxHealth * EnemyHealthScale); ;
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
	//차후 관리하는 리스트를 따로 만들것.
	//TArray<AActor*> Enemies;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAiRtanny::StaticClass(), Enemies);
	return Enemies.Num();
}

void AEnemySpawner::RemoveEnemy(AActor* EnemyInstance)
{
	if (Enemies.Contains(EnemyInstance)) {
		Enemies.Remove(EnemyInstance);
	}
}

void AEnemySpawner::CheckWaveEvents()
{
	ASurvivorGameState* VSGameState = GetWorld()->GetGameState<ASurvivorGameState>();
	if (!VSGameState || !VSGameState->IsStatePlaying())
	{
		return;
	}

	for (FVSWaveSpawnEvent& WaveEvent : WaveEvents)
	{
		if (WaveEvent.bTriggered)
		{
			continue;
		}

		if (VSGameState->ElapsedTime >= WaveEvent.TriggerTime)
		{
			TriggerWaveEvent(WaveEvent);
			WaveEvent.bTriggered = true;
		}
	}
}

void AEnemySpawner::TriggerWaveEvent(FVSWaveSpawnEvent& WaveEvent)
{
	if (!WaveEvent.EnemyClass || !TargetPlayer)
	{
		return;
	}

	switch (WaveEvent.SpawnShape)
	{
	case EVSWaveSpawnShape::CircleAroundPlayer:
		SpawnCircleWave(WaveEvent);
		break;

	case EVSWaveSpawnShape::LineFromRandomSide:
		SpawnLineWave(WaveEvent);
		break;

	default:
		SpawnCircleWave(WaveEvent);
		break;
	}
}

void AEnemySpawner::SpawnCircleWave(const FVSWaveSpawnEvent& WaveEvent)
{
	//광기의숲 1차보스몹 그거
	if (!TargetPlayer || !WaveEvent.EnemyClass)
	{
		return;
	}

	const FVector PlayerLocation = TargetPlayer->GetActorLocation();

	for (int32 i = 0; i < WaveEvent.SpawnCount; ++i)
	{
		const float Angle = 360.0f * static_cast<float>(i) / static_cast<float>(WaveEvent.SpawnCount);

		const FVector Direction = FVector(
			FMath::Cos(FMath::DegreesToRadians(Angle)),
			FMath::Sin(FMath::DegreesToRadians(Angle)),
			0.0f
		);

		const FVector SpawnLocation = PlayerLocation + Direction * WaveEvent.SpawnDistance;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ASurvivorEnemyBase* SpawnedActor = GetWorld()->SpawnActor<ASurvivorEnemyBase>(
			WaveEvent.EnemyClass,
			SpawnLocation,
			Direction.Rotation(),
			SpawnParams
		);
		if (SpawnedActor) {
			SpawnedActor->HealthComponent->SetMaxHealth(SpawnedActor->HealthComponent->MaxHealth * EnemyHealthScale); ;

			//기본 컨트롤러 미할당 시 움직이지 않음
			SpawnedActor->SpawnDefaultController();
			SpawnedActor->SetActorTickEnabled(true);
		}
	}
}

void AEnemySpawner::SpawnLineWave(const FVSWaveSpawnEvent& WaveEvent)
{
	//박쥐떼(Bat Swarm)? 일자로 스폰후 직진만하도록함
	if (!TargetPlayer || !WaveEvent.EnemyClass)
	{
		return;
	}

	const FVector PlayerLocation = TargetPlayer->GetActorLocation();

	const FVector ForwardDirection = GetRandomDirection2D();
	const FVector RightDirection = FVector::CrossProduct(FVector::UpVector, ForwardDirection).GetSafeNormal();

	const FVector CenterLocation = PlayerLocation + ForwardDirection * WaveEvent.SpawnDistance;

	const int32 HalfCount = WaveEvent.SpawnCount / 2;

	for (int32 i = 0; i < WaveEvent.SpawnCount; ++i)
	{
		const int32 OffsetIndex = i - HalfCount;
		const FVector SpawnLocation = CenterLocation + RightDirection * OffsetIndex * WaveEvent.SpawnSpacing;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AEnemy_Bat* SpawnedActor = GetWorld()->SpawnActor<AEnemy_Bat>(
			WaveEvent.EnemyClass,
			SpawnLocation,
			(-ForwardDirection).Rotation(),
			SpawnParams
		);

		if (SpawnedActor) {
			SpawnedActor->HealthComponent->SetMaxHealth(SpawnedActor->HealthComponent->MaxHealth * EnemyHealthScale); ;
			SpawnedActor->SpawnDefaultController();
			SpawnedActor->SetActorTickEnabled(true);
		}
	}
}

FVector AEnemySpawner::GetRandomDirection2D() const
{
	const float Angle = FMath::RandRange(0.0f, 360.0f);

	return FVector(
		FMath::Cos(FMath::DegreesToRadians(Angle)),
		FMath::Sin(FMath::DegreesToRadians(Angle)),
		0.0f
	).GetSafeNormal();
}

