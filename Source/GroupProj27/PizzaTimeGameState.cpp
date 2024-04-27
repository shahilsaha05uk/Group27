// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaTimeGameState.h"

#include "Subsystems/CalenderSubsystem.h"
#include "Subsystems/PizzaSubsystem.h"
#include "Subsystems/ResourceSubsystem.h"

void APizzaTimeGameState::BeginPlay()
{
	mResourceSubsystem = GetWorld()->GetSubsystem<UResourceSubsystem>();
	if(mResourceSubsystem)
	{
		mResourceSubsystem->OnBalanceUpdate.AddDynamic(this, &ThisClass::OnMoneyUpdated);
	}
	CalenderSubsystem = GetWorld()->GetSubsystem<UCalenderSubsystem>();

	mPizzaSubsystem = GetWorld()->GetSubsystem<UPizzaSubsystem>();
	if(mPizzaSubsystem)
	{
		//mPizzaSubsystem->OnAllOrdersComplete.AddDynamic(this, &ThisClass::OnMoneyUpdated);
	}
	
	Super::BeginPlay();
}

void APizzaTimeGameState::OnMoneyUpdated(int CurentBalance)
{
	
}
