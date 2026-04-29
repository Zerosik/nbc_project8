// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SurvivorRunState.h"
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "SurvivorGameState.generated.h"

//이벤트 선언, (델리게이트, 타입, 변수명)
//2개 이상의 파라미터를 쓰고싶다면 마지막의 OneParam을 변경가능.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRunStateChanged, ESurvivorRunState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKillCountChanged, int32, NewKillCount);


UCLASS()
class HOMEWORK8_API ASurvivorGameState : public AGameState
{
	GENERATED_BODY()
public:
	ASurvivorGameState();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time")
	ESurvivorRunState RunState = ESurvivorRunState::Waiting;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Time")
	float SurvivedTime = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level")
	int32 KillCount = 0;

	UPROPERTY(BlueprintAssignable)
	FOnRunStateChanged OnRunStateChanged;

	UPROPERTY(BlueprintAssignable)
	FOnKillCountChanged OnKillCountChanged;

	UFUNCTION(BlueprintCallable)
	void SetRunState(ESurvivorRunState NewState);

	UFUNCTION(BlueprintCallable)
	void AddKillCount();

	UFUNCTION(BlueprintCallable)
	bool IsStatePlaying() const;
};
