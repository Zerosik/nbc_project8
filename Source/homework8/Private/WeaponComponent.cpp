// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "WeaponProjectile.h"
#include "SurvivorEnemyBase.h"
#include "Kismet/GameplayStatics.h"
// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!ProjectileClass || !GetWorld())
		return;

	//누적시간-마지막으로 공격한시간 < 쿨타임
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastAttackTime < AttackCooldown)
		return;

	AActor* Target = FindNearestEnemy();
	if (!Target)
		return;

	FireAtTarget(Target);
	LastAttackTime = CurrentTime;
}

AActor* UWeaponComponent::FindNearestEnemy() const
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return nullptr;
	TArray<AActor*>Enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASurvivorEnemyBase::StaticClass(), Enemies);
	
	AActor* NearestEnemy = nullptr;
	float NearestDistSq = AttackRange * AttackRange;

	const FVector OwnerLocation = Owner->GetActorLocation();
	for (AActor* Enemy : Enemies) {
		if(!Enemy)
			continue;
		const float DistSq = FVector::DistSquared(OwnerLocation, Enemy->GetActorLocation());        
		//거리제곱이 가장 작은 = 공격범위내에서 가장 가까운 적을 저장
		if (DistSq < NearestDistSq)
		{
			NearestDistSq = DistSq;
			NearestEnemy = Enemy;
		}
	}
	return NearestEnemy;
}

void UWeaponComponent::FireAtTarget(AActor* Target)
{
	AActor* Owner = GetOwner();
	if (!Owner || !Target || !ProjectileClass)
		return;

	FVector Direction = Target->GetActorLocation() - Owner->GetActorLocation();
	Direction.Z = 0.f
		;
	if (Direction.IsNearlyZero())
		return;
	Direction.Normalize();

	const FVector SpawnLocation = Owner->GetActorLocation() + Direction * SpawnOffset;
	const FRotator SpawnRotation = Direction.Rotation();

	GetWorld()->SpawnActor<AWeaponProjectile>(
		ProjectileClass,
		SpawnLocation,
		SpawnRotation
	);

}

