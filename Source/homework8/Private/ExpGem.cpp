// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpGem.h"
#include "Components/SphereComponent.h"
#include "homework8/homework8Character.h"
#include "ExperienceComponent.h"
// Sets default values
AExpGem::AExpGem()
{
 	PrimaryActorTick.bCanEverTick = false;
	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	Collision->SetSphereRadius(50.f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AExpGem::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AExpGem::OnGemOverlap);
}

void AExpGem::OnGemOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	Ahomework8Character* Player = Cast<Ahomework8Character>(OtherActor);
	if (!Player || !Player->HealthComponent)
		return;
	Player->ExperienceComponent->AddExp(ExpAmount);
	Destroy();

}
