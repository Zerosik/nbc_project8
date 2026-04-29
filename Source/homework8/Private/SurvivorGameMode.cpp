// Fill out your copyright notice in the Description page of Project Settings.

#include "SurvivorGameMode.h"
#include "SurvivorGameState.h"
#include "SurvivorPlayerController.h"
#include "kismet/GameplayStatics.h"
#include "EnemySpawner.h"
#include "SurvivorGameInstance.h"
#include "ExperienceComponent.h"
#include "homework8/homework8Character.h"

ASurvivorGameMode::ASurvivorGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = ASurvivorPlayerController::StaticClass();
	GameStateClass = ASurvivorGameState::StaticClass();

	//기본생성 탑뷰캐릭터 일단 그대로 사용함.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASurvivorGameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, FString::Printf(TEXT("GameMode BeginPlay")));
	StartRun();
}

void ASurvivorGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ASurvivorGameState* SGS = GetGameState<ASurvivorGameState>();
	if (!SGS || bRunEnded)
		return;

	if (SGS->RunState == ESurvivorRunState::Playing and
		SGS->ElapsedTime >= ClearTime) {
		//승리시간까지 살아남으면 엔드
		EndRun(true);
	}

}

void ASurvivorGameMode::StartRun()
{
	bRunEnded = false;

	//게임스테이트 초기화
	ASurvivorGameState* SGS = GetGameState<ASurvivorGameState>();
	if (SGS) {
		SGS->ElapsedTime = 0.f;
		SGS->KillCount = 0;
		SGS->SetRunState(ESurvivorRunState::Playing);
	}

	CreateSpawnerIfNeeded();
	if (EnemySpawner) {
		EnemySpawner->StartSpawning();
	}
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController()) {
		if (ASurvivorPlayerController* SPC = Cast<ASurvivorPlayerController>(PlayerController)) {
			SPC->ShowGameHUD();
		}
	}
}

void ASurvivorGameMode::EndRun(bool bVictory)
{
	if (bRunEnded)
		return;
	bRunEnded = true;

	if (EnemySpawner) {
		EnemySpawner->StopSpawning();
	}

	if (bVictory) {
		HandleStageClear();
	}
	else {
		HandlePlayerDead();
	}



}

void ASurvivorGameMode::CreateSpawnerIfNeeded()
{
	if (EnemySpawner || !SpawnerClass)
		return;

	EnemySpawner = GetWorld()->SpawnActor<AEnemySpawner>(
		SpawnerClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator
	);
}

void ASurvivorGameMode::HandleStageClear()
{

	ASurvivorGameState* SGS = GetGameState<ASurvivorGameState>();
	if (SGS) {
		//승리시 Victory 패배시 GameOver
		SGS->SetRunState(ESurvivorRunState::Victory);
	}
	SaveResultToGameInstance(true);
	USurvivorGameInstance* GI = Cast<USurvivorGameInstance>(GetGameInstance());

	if (!GI)
	{
		ShowFinalResult(true);
		return;
	}
	Ahomework8Character* Player = Cast<Ahomework8Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (Player) {
		GI->PlayerExpLastStage = Player->ExperienceComponent->CurrentExp;
		GI->PlayerLevelLastStage = Player->ExperienceComponent->CurrentLevel;
	}

	if (GI->HasNextStage())
	{
		//다음스테이지로
		OpenNextStage();
	}
	else
	{
		//결과창
		GI->SetRunVictory(true);
		ShowFinalResult(true);
	}
}

void ASurvivorGameMode::HandlePlayerDead()
{
	ASurvivorGameState* VSGameState = GetGameState<ASurvivorGameState>();
	if (VSGameState)
	{
		VSGameState->SetRunState(ESurvivorRunState::GameOver);
	}

	SaveResultToGameInstance(false);

	USurvivorGameInstance* GI = Cast<USurvivorGameInstance>(GetGameInstance());
	if (GI)
	{
		GI->SetRunVictory(false);
		GI->PlayerExpLastStage = 0;
		GI->PlayerLevelLastStage = 1;

	}

	ShowFinalResult(false);

}

void ASurvivorGameMode::SaveResultToGameInstance(bool bStageCleared)
{
	USurvivorGameInstance* SGI = Cast<USurvivorGameInstance>(GetGameInstance());
	ASurvivorGameState* SGS = GetGameState<ASurvivorGameState>();
	Ahomework8Character* Player = Cast<Ahomework8Character>(UGameplayStatics::GetPlayerPawn(this, 0));

	if (!SGI || !SGS)
		return;

	int32 PlayerLevel = 1;

	if (Player && Player->ExperienceComponent) {
		PlayerLevel = Player->ExperienceComponent->CurrentLevel;
	}
	if (bStageCleared) {
		SGI->AddStageResult(
			SGS->ElapsedTime,
			SGS->KillCount,
			PlayerLevel
		);
		SGI->SetRunVictory(true);
	}
	else {
		SGI->AddStageResult(
			SGS->ElapsedTime,
			SGS->KillCount,
			PlayerLevel
		);
	}
}
void ASurvivorGameMode::OpenNextStage()
{
	USurvivorGameInstance* GI = Cast<USurvivorGameInstance>(GetGameInstance());
	if (!GI){
		return;
	}

	const FName NextStageName = GI->MoveToNextStageAndGetLevelName();
	if (NextStageName == NAME_None)
	{
		ShowFinalResult(true);
		return;
	}
	int32 newStageIndex = GI->GetCurrentStageNumber();
	OnStageChanged.Broadcast(newStageIndex);
	UGameplayStatics::OpenLevel(this, NextStageName);
}

void ASurvivorGameMode::ShowFinalResult(bool bVictory)
{
	if (ASurvivorPlayerController* PC = Cast<ASurvivorPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PC->ShowResultWidget(bVictory);
	}
}

