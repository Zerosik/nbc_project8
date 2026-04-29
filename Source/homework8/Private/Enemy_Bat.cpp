// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy_Bat.h"
#include "Kismet/GameplayStatics.h"

AEnemy_Bat::AEnemy_Bat()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 5;
	MoveSpeed = 500;
}

void AEnemy_Bat::BeginPlay()
{
	Super::BeginPlay();
	APawn* TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
	direction = TargetPlayer->GetActorLocation() - GetActorLocation();
	direction.Z = 0;
	if (!direction.IsNearlyZero())
		direction.Normalize();
	SetActorTickEnabled(true);
}

void AEnemy_Bat::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	MoveToDirection(DeltaSeconds);
}


void AEnemy_Bat::MoveToDirection(float DeltaTime)
{
	//방향안바꾸고 직진갈김
	AddMovementInput(direction, 1.f);
}

void AEnemy_Bat::HandleDeath()
{
	Super::HandleDeath();
}

void AEnemy_Bat::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}