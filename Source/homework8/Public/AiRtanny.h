// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AiRtanny.generated.h"

class UHealthComponent;
class AExpGem;

UCLASS()
class HOMEWORK8_API AAiRtanny : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAiRtanny();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MoveSpeed = 250;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ContractGamage = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DamageInterval = .5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AExpGem> ExpGemClass;

protected:
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	AActor* TargetPlayer;

	//마지막으로 데미지를 입힌 시간
	float LastDamageTime = -999.f;
	
	void MoveToPlayer(float DeltaTime);

	UFUNCTION()
	void HandleDeath();

	UFUNCTION()
	void OnEnemyOvelap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

};
