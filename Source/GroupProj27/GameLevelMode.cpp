// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelMode.h"

#include "Subsystems/CalenderSubsystem.h"
#include "Subsystems/PizzaSubsystem.h"
#include "Subsystems/ResourceSubsystem.h"


void AGameLevelMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	bHasReached = false;

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
	}
	if(ResourceSubsystem)
	{
		// Adds the starting balance to the current balamce
		ResourceSubsystem->AddBalance(mStartingBalance);
	}
}

void AGameLevelMode::RequestForOrders_Implementation()
{
	
}

#pragma region Calender Bind methods

void AGameLevelMode::StartDay_Implementation()
{
	if(CalenderSubsystem) CalenderSubsystem->OnFinishCountdown.Broadcast();
	OnStrikesUpdated.Broadcast(CurrentStrikes);
	Execute_RequestForOrders(this);
}

void AGameLevelMode::FinishDay_Implementation()
{
	
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
		CalenderSubsystem->StartCountdown(mCountdownDuration, mRate);
	}
}

#pragma endregion

#pragma region Interface Methods

void AGameLevelMode::MakeDecisionBasedOnMoney_Implementation(int CurrentBalance)
{
	
}

void AGameLevelMode::OnPlayerArrival_Implementation(EPlayerArrivalStatus Status)
{
	//OnPlayerArrivedAtTheShop.Broadcast(HasReachedShop);

	switch (Status)
	{
	case ARRIVED:
		CalenderSubsystem->EndCountdown();
		if (PizzaSubsystem->CanTakeOrders())
		{
			CalenderSubsystem->StartDay();
		}
		break;
	case YET_TO_ARRIVE:
		break;
	case LATE:
		if (PizzaSubsystem->CanTakeOrders())
		{
			//TODO: Needs to be looked at
			//CalenderSubsystem->StartDay();
		}
		break;
	default:
		break;
	}
	OnPlayerArrivedAtTheShop.Broadcast(Status);
}

#pragma endregion
