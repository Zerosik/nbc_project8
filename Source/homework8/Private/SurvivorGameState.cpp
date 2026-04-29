// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorGameState.h"

ASurvivorGameState::ASurvivorGameState() 
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASurvivorGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RunState == ESurvivorRunState::Playing) {
		SurvivedTime += DeltaTime;
	}
	//if (ClearTime < SurvivedTime) {
	//	//시간 클리어
	//	SetRunState(ESurvivorRunState::Victory);

	//}
}

void ASurvivorGameState::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, FString::Printf(TEXT("Survivor GameState BeginPlay")));
	
}

void ASurvivorGameState::SetRunState(ESurvivorRunState NewState)
{
	if (RunState == NewState)
		return;
	RunState = NewState;
	OnRunStateChanged.Broadcast(RunState);
}

void ASurvivorGameState::AddKillCount()
{
	KillCount++;
	OnKillCountChanged.Broadcast(KillCount);
}

bool ASurvivorGameState::IsStatePlaying() const
{
	return RunState == ESurvivorRunState::Playing;
}
