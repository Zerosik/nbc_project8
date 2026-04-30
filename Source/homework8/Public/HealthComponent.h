// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOMEWORK8_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetMaxHealth(float newHealth);

	UFUNCTION(BlueprintCallable)
	void TakeDamageValue(float Damage);

	UFUNCTION(BlueprintCallable)
	void Heal(float Amount);

	UFUNCTION(BlueprintCallable)
	float GetHealthRatio() const;
		
	float CurrentHealth = 100.f;
	float MaxHealth = 100.f;
	bool bDead = false;
	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

};
/*
체력-이벤트와 사망시 액션,
체력 잃음/회복
UI연동을 위한 이벤트,
사망 이벤트
*/