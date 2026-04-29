// Fill out your copyright notice in the Description page of Project Settings.


#include "ExperienceComponent.h"

// Sets default values for this component's properties
UExperienceComponent::UExperienceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UExperienceComponent::AddExp(int32 Amount)
{
	if (Amount <= 0)
		return;

	CurrentExp += Amount;

	//들어온경험치가 2회이상 레벨업일수있음
	while(CurrentExp >= RequiredExp) {
		CurrentExp -= RequiredExp;
		CurrentLevel++;
		RequiredExp = CalcRequiredExp(CurrentLevel);
		OnLevelUp.Broadcast(CurrentLevel);
	}
	OnExpChanged.Broadcast(
		CurrentExp,
		RequiredExp,
		CurrentLevel);
}

int32 UExperienceComponent::CalcRequiredExp(int32 Level) const
{
/*
https://vampire.survivors.wiki/w/Level_up
X to Y level require exp
Levels 2–20: (next level * 10) -5
Levels 21–40: (next level * 13) -6
Levels 41+: (next level * 16) -8
*/
	int32 newRequiredExp;
	if (Level <= 20) {
		newRequiredExp = (Level * 10) - 5;
	}
	else if (Level <= 40) {
		newRequiredExp = (Level * 13) - 6;
	}
	else {
		newRequiredExp = (Level * 16) - 8;
	}
	return newRequiredExp;
}
