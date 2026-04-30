// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class HOMEWORK8_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponProjectile();

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Weapon Stats")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	float LifeTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Stats")
	int32 PierceCount = 1;

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	TArray<AActor*> HitActors;

    UFUNCTION()
    void OnProjectileOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

};
