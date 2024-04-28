// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelMode.h"

#include "Subsystems/CalenderSubsystem.h"
#include "Subsystems/PizzaSubsystem.h"
#include "Subsystems/ResourceSubsystem.h"


void AGameLevelMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	const auto Instance = GetGameInstance();
	PizzaSubsystem = Instance->GetSubsystem<UPizzaSubsystem>();
	CalenderSubsystem = Instance->GetSubsystem<UCalenderSubsystem>();
	ResourceSubsystem = Instance->GetSubsystem<UResourceSubsystem>();
	
	if(PizzaSubsystem)
	{
		PizzaSubsystem->OnReadyToTakeOrder.AddDynamic(this, &ThisClass::OnReadyToTakeOrder);
		PizzaSubsystem->OnOrderComplete.AddDynamic(this, &ThisClass::OnOrderComplete);
		PizzaSubsystem->OnAllOrdersComplete.AddDynamic(this, &ThisClass::OnAllOrdersComplete);
	}
	if(CalenderSubsystem)
	{
		CalenderSubsystem->OnDayStarted.AddDynamic(this, &ThisClass::StartDay);
		CalenderSubsystem->OnDayComplete.AddDynamic(this, &ThisClass::FinishDay);
		CalenderSubsystem->OnWeekComplete.AddDynamic(this, &ThisClass::OnWeekComplete);
		CalenderSubsystem->OnStartCountdown.AddDynamic(this, &ThisClass::OnCountdownStart);
		CalenderSubsystem->OnFinishCountdown.AddDynamic(this, &ThisClass::OnCountdownEnd);
	}
	if(ResourceSubsystem)
	{
		ResourceSubsystem->AddBalance(mStartingBalance);
	}
}

void AGameLevelMode::RequestForOrders_Implementation()
{
	
}

#pragma region Private methods

#pragma endregion

#pragma region Calender Bind methods

void AGameLevelMode::StartDay_Implementation()
{
	if(CalenderSubsystem) CalenderSubsystem->OnFinishCountdown.Broadcast();
	OnStrikesUpdated.Broadcast(CurrentStrikes);
	Execute_RequestForOrders(this);
}

void AGameLevelMode::FinishDay_Implementation(bool HasReached)
{
	if(HasReached)
	{
		CalenderSubsystem->OnFinishCountdown.Broadcast();
	}
}

void AGameLevelMode::OnWeekComplete_Implementation()
{
	if(!HasEnoughBalanceToPayRent())	// if the balance is not enough to pay the rent
	{
		OnStrikesUpdated.Broadcast(CurrentStrikes++);
		const auto decision = (CurrentStrikes >= TotalStrikes)? LOSE: CONTINUE;
		OnDecisionMade.Broadcast(decision);
		return;
	}
	OnDecisionMade.Broadcast(WIN);
}

#pragma endregion

#pragma region PizzaSubsystem Bind Methods

void AGameLevelMode::OnReadyToTakeOrder_Implementation()
{
	
}

void AGameLevelMode::OnOrderComplete_Implementation(int CustomerID, FPizzaStruct OrderSummary)
{
	auto balance = ResourceSubsystem->AddBalance(ResourceToAdd);
	
	//Check the current balance to see if the they can pay the rent
	const auto decision = (balance > TargetResourceThreshold)? WIN: CONTINUE;
	OnDecisionMade.Broadcast(decision);
}

void AGameLevelMode::OnAllOrdersComplete_Implementation()
{
	if(CalenderSubsystem)
	{
		CalenderSubsystem->OnStartCountdown.Broadcast(mCountdownDuration, mRate);
	}
}

#pragma endregion

#pragma region TimerSubsystem

void AGameLevelMode::OnCountdownStart_Implementation(float Duration, float Rate)
{
}

void AGameLevelMode::OnCountdownEnd_Implementation()
{
	//FinishDay(bHasReachedShop);
}

#pragma endregion

#pragma region Interface Methods

void AGameLevelMode::MakeDecisionBasedOnMoney_Implementation(int CurrentBalance)
{
	
}

#pragma endregion
