// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "homework8/homework8Character.h"
#include "MainMenuPlayerController.h"
#include "SurvivorGameState.h"
#include "SurvivorGameInstance.h"
#include "ResultWidget.h"

ASurvivorPlayerController::ASurvivorPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ASurvivorPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
        EnhancedInputComponent->BindAction(TopdownMoveAction, ETriggerEvent::Triggered, this, &ASurvivorPlayerController::OnMoveTriggered);
        EnhancedInputComponent->BindAction(TopdownMoveAction, ETriggerEvent::Completed, this, &ASurvivorPlayerController::OnMoveTriggered);

        EnhancedInputComponent->BindAction(ManualAttackAction, ETriggerEvent::Triggered, this, &ASurvivorPlayerController::OnManualAttackTriggered);
        EnhancedInputComponent->BindAction(ManualAttackAction, ETriggerEvent::Completed, this, &ASurvivorPlayerController::OnMoveCompleted);


        EnhancedInputComponent->BindAction(PauseGameAction, ETriggerEvent::Started, this, &ASurvivorPlayerController::TogglePauseWidget);
        

	}
}

void ASurvivorPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
    SetInputMode(FInputModeGameOnly());
    ShowGameHUD();
}

void ASurvivorPlayerController::OnMoveTriggered(const FInputActionValue& value)
{
	const FVector2D moveInput = value.Get<FVector2D>();
    if (moveInput.IsNearlyZero())
        return;
	

    APawn* controlledPawn = GetPawn();

    float DeltaTime = GetWorld()->GetDeltaSeconds();
    float MoveSpeed = 600.f;
    controlledPawn->AddMovementInput(FVector(moveInput * DeltaTime * MoveSpeed, 0.0f));

}

void ASurvivorPlayerController::OnMoveCompleted(const FInputActionValue& value)
{
    Ahomework8Character* controlledPawn = Cast<Ahomework8Character>(GetPawn());
    if (controlledPawn) {
        controlledPawn->SetIsManuallyControlled(false);
    }
}

void ASurvivorPlayerController::OnManualAttackTriggered(const FInputActionValue& value)
{
    return;
    float DeltaTime = GetWorld()->GetDeltaSeconds();
	FHitResult TraceResult;
    GetHitResultUnderCursor(ECC_Visibility, true, TraceResult);

    if (TraceResult.bBlockingHit)
    {
        Ahomework8Character* controlledPawn = Cast<Ahomework8Character>(GetPawn());

        controlledPawn->SetIsManuallyControlled(true);

        FVector MouseLocation = TraceResult.ImpactPoint;
        FVector CharacterLocation = controlledPawn->GetActorLocation();

        // 탑뷰이므로 Z 축은 같게 설정하여 평면 회전만 고려
        MouseLocation.Z = CharacterLocation.Z;

        // 바라봐야 할 방향 벡터
        FVector Direction = (MouseLocation - CharacterLocation).GetSafeNormal();

        // 1. 단순 즉시 회전 (Snap)
        // SetActorRotation(Direction.Rotation());

        // 2. 부드러운 회전 (RInterpTo 사용)
        FRotator NewRotation = Direction.Rotation();
        FRotator CurrentRotation = controlledPawn->GetActorRotation();

        // Yaw(좌우) 값만 부드럽게 회전
        FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, NewRotation, DeltaTime, 10.0f);
        controlledPawn->SetActorRotation(FRotator(0.0f, SmoothRotation.Yaw, 0.0f));
        
    }
}

void ASurvivorPlayerController::ShowLevelUPWidget()
{
}

void ASurvivorPlayerController::CloseLevelUPWidget()
{
}

void ASurvivorPlayerController::TogglePauseWidget()
{
    ASurvivorGameState* AGS = GetWorld()->GetGameState<ASurvivorGameState>();
    if (AGS->RunState == ESurvivorRunState::Playing) {
        //정지
        AGS->SetRunState(ESurvivorRunState::Waiting);
        if (PauseMenuWidgetClass) {
            PauseMenuWidgetInstance = CreateWidget<UUserWidget>(this, PauseMenuWidgetClass);
            if (PauseMenuWidgetInstance) {
                PauseMenuWidgetInstance->AddToViewport();
            }
        }
        SetPause(true);
    }
    else if (AGS->RunState == ESurvivorRunState::Waiting) {
        //다시시작
        AGS->SetRunState(ESurvivorRunState::Playing);
        if (PauseMenuWidgetInstance) {
            PauseMenuWidgetInstance->RemoveFromParent();
            PauseMenuWidgetInstance = nullptr;
        }
        SetPause(false);
    }

}


void ASurvivorPlayerController::ShowResultWidget(bool bVictory)
{
    USurvivorGameInstance* SGI = Cast<USurvivorGameInstance>(GetGameInstance());
    ASurvivorGameState* AGS = GetWorld()->GetGameState<ASurvivorGameState>();
    ClearUI();
    AGS->SetRunState(ESurvivorRunState::GameOver);
    if (ResultWidgetClass) {
        ResultWidgetInstance = CreateWidget<UResultWidget>(this, ResultWidgetClass);
        if (ResultWidgetInstance) {
            ResultWidgetInstance->AddToViewport();
            ResultWidgetInstance->SetupResult(bVictory);
        }
    }
}

void ASurvivorPlayerController::CloseResultWidget()
{
}

void ASurvivorPlayerController::ShowGameHUD()
{
    ClearUI();
    if (GameHUDWidgetClass) {
        GameHUDWidgetInstance = CreateWidget<UUserWidget>(this, GameHUDWidgetClass);
        if (GameHUDWidgetInstance) {
            GameHUDWidgetInstance->AddToViewport();
        }
    }
}

void ASurvivorPlayerController::CloseGameHUD()
{
}


void ASurvivorPlayerController::ReturnToMainMenu()
{
    SetPause(false);
    UGameplayStatics::OpenLevel(this, MainMenuLevelName);
}

void ASurvivorPlayerController::ClearUI()
{
    if (LevelUPMenuWidgetInstance) {
        LevelUPMenuWidgetInstance->RemoveFromParent();
        LevelUPMenuWidgetInstance = nullptr;
    }
    if (PauseMenuWidgetInstance) {
        PauseMenuWidgetInstance->RemoveFromParent();
        PauseMenuWidgetInstance = nullptr;
    }
    if (GameHUDWidgetInstance) {
        GameHUDWidgetInstance->RemoveFromParent();
        GameHUDWidgetInstance = nullptr;
    }
}
