// Copyright Epic Games, Inc. All Rights Reserved.

#include "homework8Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "SurvivorGameMode.h"
#include "kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "ExperienceComponent.h"
#include "WeaponComponent.h"
#include "SurvivorGameInstance.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"
Ahomework8Character::Ahomework8Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	HpBarWIdget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBarWidget"));
	HpBarWIdget->SetupAttachment(GetMesh());
	HpBarWIdget->SetWidgetSpace(EWidgetSpace::Screen);


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;


	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	ExperienceComponent = CreateDefaultSubobject<UExperienceComponent>(TEXT("ExperienceComponent"));
	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void Ahomework8Character::BeginPlay()
{
	Super::BeginPlay();
	bIsManuallyControlled = false;

	USurvivorGameInstance* GI = Cast<USurvivorGameInstance>(GetGameInstance());
	FPlayerRunStatus PlayerStatus = GI->GetPrevPlayerStatus();
	FPlayerWeaponStatus WeaponStatus = GI->GetPrevWeaponStatus();
	if (HealthComponent) {
		HealthComponent->CurrentHealth = PlayerStatus.CurrentHealth;
		HealthComponent->OnDeath.AddDynamic(this, &Ahomework8Character::HandleDeath);
		HealthComponent->OnHealthChanged.AddDynamic(this, &Ahomework8Character::UpdateHpBar);
	}
	if (ExperienceComponent) {
		ExperienceComponent->CurrentLevel = PlayerStatus.Level;
		ExperienceComponent->CurrentExp = PlayerStatus.CurrentExp;
		ExperienceComponent->RequiredExp = PlayerStatus.RequiredExp;
	}
	if (WeaponComponent) {
		WeaponComponent->Damage = WeaponStatus.Damage;
		WeaponComponent->MultiShotCount = WeaponStatus.MultiShotCount;
		WeaponComponent->PierceCount = WeaponStatus.PierceCount;
		WeaponComponent->MultiShotAngle = WeaponStatus.MultiShotAngle;
	}

}

void Ahomework8Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}


void Ahomework8Character::SetIsManuallyControlled(bool bIsManual) {

	bIsManuallyControlled = bIsManual; 
	GetCharacterMovement()->bOrientRotationToMovement = !bIsManual;
}

void Ahomework8Character::HandleDeath()
{
	if (ASurvivorGameMode* SGM = Cast<ASurvivorGameMode>(UGameplayStatics::GetGameMode(this))) {
		SGM->EndRun(false);
	}
}

void Ahomework8Character::UpdateHpBar(float CurrentHealth, float MaxHealth)
{
	if (!HpBarWIdget)
		return;

	UUserWidget* HpBarWIdgetInstance = HpBarWIdget->GetUserWidgetObject();
	if (!HpBarWIdgetInstance)
		return;

	if (UProgressBar* HpBar = Cast<UProgressBar>(HpBarWIdgetInstance->GetWidgetFromName(TEXT("HP_Bar")))) {
		float ratio = static_cast<float>(CurrentHealth) / MaxHealth;
		HpBar->SetPercent(1.f-ratio);
	}
}
