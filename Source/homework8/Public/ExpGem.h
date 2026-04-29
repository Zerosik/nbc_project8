// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExpGem.generated.h"

class USphereComponent;

UCLASS()
class HOMEWORK8_API AExpGem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExpGem();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere)
	int32 ExpAmount = 1;



protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void OnGemOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
