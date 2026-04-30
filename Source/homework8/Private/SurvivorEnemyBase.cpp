// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorEnemyBase.h"
#include "HealthComponent.h"
#include "SurvivorGameState.h"
#include "ExpGem.h"
#include "homework8/homework8Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemySpawner.h"

// Sets default values
ASurvivorEnemyBase::ASurvivorEnemyBase()
{
	MaxHealth = 10;
	MoveSpeed = 250;
	ContractGamage = 5.f;
	DamageInterval = .5;
	ExpDrop = 1;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnDeath.AddDynamic(this, &ASurvivorEnemyBase::HandleDeath);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ASurvivorEnemyBase::OnPlayerOverlap);

}

void ASurvivorEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->MaxHealth = MaxHealth;
	if (GetCharacterMovement()) {
		//#include "GameFramework/CharacterMovementComponent.h"
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
}

void ASurvivorEnemyBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (MySpawner) {
		MySpawner->RemoveEnemy(this);
	}
	Super::EndPlay(EndPlayReason);
}


void ASurvivorEnemyBase::HandleDeath()
{
	if (ASurvivorGameState* SGS = GetWorld()->GetGameState<ASurvivorGameState>()) {
		SGS->AddKillCount();
	}
	if (ExpGemClass) {
		FActorSpawnParameters SpawnParams;
		// 충돌 발생 시에도 강제 스폰하는 설정
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//사망위치에 경험치 액터 스폰
		AExpGem* Gem = GetWorld()->SpawnActor<AExpGem>(
			ExpGemClass,
			GetActorLocation(),
			FRotator::ZeroRotator,
			SpawnParams
		);
		if(Gem)
			Gem->ExpAmount = ExpDrop;
	}
	Destroy();
}

void ASurvivorEnemyBase::OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Ahomework8Character* Player = Cast< Ahomework8Character>(OtherActor);
	if (!Player || !Player->HealthComponent)
		return;
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	//일정시간마다 피해를 입히도록 제한.
	if (CurrentTime - LastDamageTime < DamageInterval)
		return;

	LastDamageTime = CurrentTime;
	Player->HealthComponent->TakeDamageValue(ContractGamage);
}

