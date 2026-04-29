// Fill out your copyright notice in the Description page of Project Settings.


#include "AiRtanny.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "homework8/homework8Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurvivorGameState.h"
#include "ExpGem.h"
// Sets default values
AAiRtanny::AAiRtanny()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->MaxHealth = 10.f;
	
	//캐릭터는 일단 캡슐이있음
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AAiRtanny::OnEnemyOvelap);

}

// Called when the game starts or when spawned
void AAiRtanny::BeginPlay()
{
	Super::BeginPlay();
	TargetPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
	if (HealthComponent) {
		HealthComponent->OnDeath.AddDynamic(this, &AAiRtanny::HandleDeath);
	}
	
	if (GetCharacterMovement()) {
		//#include "GameFramework/CharacterMovementComponent.h"
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
	}
	
}

// Called every frame
void AAiRtanny::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToPlayer(DeltaTime);
}

void AAiRtanny::MoveToPlayer(float DeltaTime) {
	//이동은 캐릭터무브먼트컴포넌트
	if (!TargetPlayer || !HealthComponent || HealthComponent->bDead)
		return;

	FVector Direction = TargetPlayer->GetActorLocation() - GetActorLocation();
	Direction.Z = 0;
	if (!Direction.IsNearlyZero()) {
		Direction.Normalize();

		AddMovementInput(Direction, 1.f);

		FRotator LookRotation = Direction.Rotation();
		SetActorRotation(LookRotation);
	}
}

void AAiRtanny::HandleDeath() {
	if (ASurvivorGameState* SGS = GetWorld()->GetGameState<ASurvivorGameState>()) {
		SGS->AddKillCount();
	}
	if (ExpGemClass) {
		//사망위치에 경험치 액터 스폰
		GetWorld()->SpawnActor<AExpGem>(
			ExpGemClass,
			GetActorLocation(),
			FRotator::ZeroRotator
		);
	}
	//여기에 낮은확률로 경험치대신 포션등등 드랍/?
	//사망이펙트?
	Destroy();
}
void AAiRtanny::OnEnemyOvelap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
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
