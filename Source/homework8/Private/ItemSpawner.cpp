// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Item/PotionItem.h"

// Sets default values
AItemSpawner::AItemSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemSpawner::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
	
}

// Called every frame
void AItemSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//타이머로 바꾸는게 나을듯
	if (!bSpawning || !GetWorld())
		return;
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastSpawnTime >= SpawnTryInterval) {
		TrySpawnItem();
		LastSpawnTime = CurrentTime;
	}
}

void AItemSpawner::StartSpawning()
{
	bSpawning = true;
}

void AItemSpawner::StopSpawning()
{
	bSpawning = false;
}

void AItemSpawner::TrySpawnItem()
{
	//확률 체크
	if (FMath::FRand()<= BaseItemSpawnChance) {
		SpawnItem();
	}
}

void AItemSpawner::SpawnItem()
{
	//스폰
	const FVector SpawnLocation = GetRandomSpawnLocationInRange();
	APotionItem* SpawnedItem = GetWorld()->SpawnActor< APotionItem>(
		ItemClass,
		SpawnLocation,
		FRotator::ZeroRotator
	);
	//액터는 컨트롤러 필요X
}

FVector AItemSpawner::GetRandomSpawnLocationInRange() const
{
	float RandomDistance = FMath::FRandRange(SpawnMinDistanceFromPlayer, SpawnMaxDistanceFromPlayer);
	float RandomAngle = FMath::FRandRange(0.f, 360.f);
	const FVector Direction = FVector(
		FMath::Cos(FMath::DegreesToRadians((RandomAngle))),
		FMath::Sin(FMath::DegreesToRadians((RandomAngle))),
		0.f
	);
	return TargetPlayer->GetActorLocation() + Direction * RandomDistance;
}
