// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PotionItem.h"
#include "homework8/homework8Character.h"
#include "HealthComponent.h"

// Sets default values
APotionItem::APotionItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APotionItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APotionItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APotionItem::OnItemOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnItemOverlap(OverlappedComp,  OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void APotionItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);
	Ahomework8Character* Player = Cast< Ahomework8Character>(Activator);
	if (Player) {
		Player->HealthComponent->Heal(HealAmount);
	}
	DestroyItem();

}

void APotionItem::DestroyItem()
{
	Super::DestroyItem();

}

