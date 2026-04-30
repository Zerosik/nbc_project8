// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UpgradeTypes.h"
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
	float AttackRange = 2000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackCooldown = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SpawnOffset = 60.f;

	//업그레이드 값
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Stats")
    float Damage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Stats")
    int32 MultiShotCount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Stats")
    int32 PierceCount = 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Stats")
    float MultiShotAngle = 12.0f;

	UFUNCTION(BlueprintCallable)
    void ApplyWeaponUpgrade(EWeaponUpgradeStat StatType, EUpgradeValueType ValueType, float Value);


private:
	float LastAttackTime = -999.f;
	AActor* FindNearestEnemy() const;
	void FireAtTarget(AActor* Target);
	float ApplyValue(float CurrentValue, EUpgradeValueType ValueType, float Value) const;
};
