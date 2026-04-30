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
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Stats")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Stats")
	float MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Stats")
	float ContractGamage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Stats")
	float DamageInterval;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy Stats")
	int32 ExpDrop;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AExpGem> ExpGemClass;

public:
	virtual void HandleDeath() override;
	virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
private:
	float LastDamageTime = -999.f;
};
