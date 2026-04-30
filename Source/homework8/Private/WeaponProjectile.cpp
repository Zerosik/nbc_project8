// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AiRtanny.h"
#include "HealthComponent.h"

// Sets default values
AWeaponProjectile::AWeaponProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    RootComponent = Collision;

    Collision->SetSphereRadius(32.0f);
    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionResponseToAllChannels(ECR_Overlap);

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->InitialSpeed = 1000.f;
    ProjectileMovement->MaxSpeed = 1000.0f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();

    Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponProjectile::OnProjectileOverlap);
    //액터의 수명을 결정하는 기본함수, lifeSpan초 후 자동 Destroy
    //지속시간을 넣는것도?
    SetLifeSpan(LifeTime);
	
}

void AWeaponProjectile::OnProjectileOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    ASurvivorEnemyBase* Enemy = Cast<ASurvivorEnemyBase>(OtherActor);
    if (!Enemy)
        return;
    if (HitActors.Contains(Enemy))
        return;
    HitActors.Add(Enemy);

    Enemy->HealthComponent->TakeDamageValue(Damage);
    PierceCount--;
    if (PierceCount <= 0)
        Destroy();
}
