// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelMode.h"

#include "Subsystems/CalenderSubsystem.h"
#include "Subsystems/ResourceSubsystem.h"


void AGameLevelMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
	bHasReached = false;

	const auto Instance = GetGameInstance();
	CalenderSubsystem = Instance->GetSubsystem<UCalenderSubsystem>();
	ResourceSubsystem = Instance->GetSubsystem<UResourceSubsystem>();
	if(CalenderSubsystem)
	{
		CalenderSubsystem->OnDayStarted.AddDynamic(this, &ThisClass::OnDayStart);
		CalenderSubsystem->OnWeekComplete.AddDynamic(this, &ThisClass::OnWeekComplete);
	}
	if(ResourceSubsystem)
	{
		// Adds the starting balance to the current balamce
		ResourceSubsystem->AddBalance(mStartingBalance);
	}
}

#pragma region Calender Bind methods

void AGameLevelMode::OnDayStart_Implementation()
{
	OnStrikesUpdated.Broadcast(CurrentStrikes);
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

void AGameLevelMode::OnOrderComplete_Implementation(int CustomerID, FPizzaStruct OrderSummary)
{
	const auto balance = ResourceSubsystem->AddBalance(ResourceToAdd);
	
	//Check the current balance to see if the they can pay the rent
	const auto decision = (balance > TargetResourceThreshold)? WIN: CONTINUE;
	OnDecisionMade.Broadcast(decision);
}

#pragma endregion

#pragma region Interface Methods

void AGameLevelMode::RequestForOrders_Implementation()
{
}

/*
void AGameLevelMode::OnPlayerStatusUpdated_Implementation(const EPlayerArrivalStatus PlayerStatus)
{
	OnPlayerStatusUpdate.Broadcast(PlayerStatus);
	InitiateOrders(PlayerStatus);
	// if the player has arrived than start a new day

	// if the player is late than ONLY CREATE THE ORDERS AND DISPLAY THE VISUALS WHEN THE STATUS IS UPDATED TO ARRIVED
}
#pragma endregion

void AGameLevelMode::InitiateOrders_Implementation(EPlayerArrivalStatus Status)
{
	
}
*/


