// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/BaseItem.h"
#include "Components/SphereComponent.h"
#include "homework8/homework8Character.h"

// Sets default values
ABaseItem::ABaseItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
    Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Collision->SetupAttachment(Scene);
    Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnItemOverlap);

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(Collision);
    StaticMesh->SetCollisionProfileName(TEXT("NoCollision"));

}

// Called when the game starts or when spawned
void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    RunningTime += DeltaTime;

    FRotator newRotate = { 20, StaticMesh->GetRelativeRotation().Yaw + (DeltaTime * 90), 0 };
    StaticMesh->SetRelativeRotation(newRotate);
}

void ABaseItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    Ahomework8Character* Player = Cast< Ahomework8Character>(OtherActor);
    if (!Player || !Player->HealthComponent)
        return;
    ActivateItem(Player);
}

void ABaseItem::ActivateItem(AActor* Activator)
{
    //기본 효과?
}

void ABaseItem::DestroyItem()
{
    Destroy();
}

