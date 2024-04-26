// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaTimeGameState.h"

#include "Subsystems/CalenderSubsystem.h"
#include "Subsystems/ResourceSubsystem.h"

void APizzaTimeGameState::BeginPlay()
{
	mResourceSubsystem = GetWorld()->GetSubsystem<UResourceSubsystem>();
	CalenderSubsystem = GetWorld()->GetSubsystem<UCalenderSubsystem>();
	CalenderSubsystem->OnWeekUpdated.AddDynamic(this, &ThisClass::OnWeekUpdated);
	Super::BeginPlay();
}

void APizzaTimeGameState::OnWeekUpdated_Implementation(int CurrentWeek)
{
	if(mResourceSubsystem->GetCurrentBalance() < TargetResourceThreshold) CurrentStrikes++;
	
	const EGameDecision decision = (CurrentStrikes >= TargetResourceThreshold) ? LOSE : CONTINUE;

	mResourceSubsystem->DeductBalance(TargetResourceThreshold);
	CalenderSubsystem->ResetDays();
	OnGameStateProcessed.Broadcast(decision);
}

