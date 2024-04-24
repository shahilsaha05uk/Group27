// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaTimeGameState.h"

#include "DataAssets/DA_CalenderComponent.h"
#include "DataAssets/DA_ResourceComponent.h"

void APizzaTimeGameState::BeginPlay()
{
	mCalenderComp->OnWeekUpdated.AddDynamic(this, &ThisClass::OnWeekUpdated);
	Super::BeginPlay();
}

void APizzaTimeGameState::OnWeekUpdated_Implementation(int CurrentWeek)
{
	if(mResourcesComp->GetCurrentBalance() < TargetResourceThreshold) CurrentStrikes++;
	
	const EGameDecision decision = (CurrentStrikes >= TargetResourceThreshold) ? LOSE : CONTINUE;

	mResourcesComp->DeductBalance(TargetResourceThreshold);
	mCalenderComp->ResetDays();
	OnGameStateProcessed.Broadcast(decision);
}

