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
	CalenderSubsystem->UpdateCalender();

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