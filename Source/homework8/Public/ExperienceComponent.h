// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExperienceComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUp, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnExpChanged, int32, CurrentExp, int32, RequiredExp, int32, CurrentLevel);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HOMEWORK8_API UExperienceComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UExperienceComponent();

	void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentLevel = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentExp = 0;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 RequiredExp = 5;

	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnLevelUp OnLevelUp;
	
	UPROPERTY(VisibleAnywhere, BlueprintAssignable)
	FOnExpChanged OnExpChanged;

	UFUNCTION(BlueprintCallable)
	void AddExp(int32 NewLevel);

	int32 CalcRequiredExp(int32 Level) const;

private:


};

