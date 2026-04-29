// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeaponProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEWORK8_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWeaponProjectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackRange = 5000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackCooldown = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnOffset = 60.f;

private:
	float LastAttackTime = -999.f;
	AActor* FindNearestEnemy() const;
	void FireAtTarget(AActor* Target);
		
};
