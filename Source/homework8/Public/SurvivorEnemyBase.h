// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivorEnemyInterface.h"
#include "SurvivorEnemyBase.generated.h"

class UHealthComponent;
class AExpGem;

UCLASS()
class HOMEWORK8_API ASurvivorEnemyBase : public ACharacter, public ISurvivorEnemyInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASurvivorEnemyBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHealth = 10;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed = 250;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ContractGamage = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DamageInterval = .5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ExpDrop = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AExpGem> ExpGemClass;

public:
	virtual void HandleDeath() override;
	virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:
	float LastDamageTime = -999.f;
};
