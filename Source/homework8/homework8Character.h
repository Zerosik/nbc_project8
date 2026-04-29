// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "homework8Character.generated.h"

class UHealthComponent;
class UExperienceComponent;
class UWeaponComponent;

UCLASS(Blueprintable)
class Ahomework8Character : public ACharacter
{
	GENERATED_BODY()

public:
	Ahomework8Character();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* HealthComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UExperienceComponent* ExperienceComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWeaponComponent* WeaponComponent;
	





	UFUNCTION(BlueprintPure)
	inline bool GetIsManuallyControlled() { return bIsManuallyControlled; }
	UFUNCTION(BlueprintCallable)
	void SetIsManuallyControlled(bool bIsManual);

private:
	UFUNCTION()
	void HandleDeath();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	bool bIsManuallyControlled = false;
};

