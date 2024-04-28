// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelMode.h"

#include "Subsystems/CalenderSubsystem.h"
#include "Subsystems/PizzaSubsystem.h"
#include "Subsystems/ResourceSubsystem.h"
#include "Subsystems/TimerSubsystem.h"


void AGameLevelMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	const auto Instance = GetGameInstance();
	PizzaSubsystem = Instance->GetSubsystem<UPizzaSubsystem>();
	TimerSubsystem = Instance->GetSubsystem<UTimerSubsystem>();
	CalenderSubsystem = Instance->GetSubsystem<UCalenderSubsystem>();
	ResourceSubsystem = Instance->GetSubsystem<UResourceSubsystem>();
	
	if(PizzaSubsystem)
	{
		PizzaSubsystem->OnReadyToTakeOrder.AddDynamic(this, &ThisClass::OnReadyToTakeOrder);
		PizzaSubsystem->OnOrderComplete.AddDynamic(this, &ThisClass::OnOrderComplete);
		PizzaSubsystem->OnAllOrdersComplete.AddDynamic(this, &ThisClass::OnAllOrdersComplete);
	}
	if(TimerSubsystem)
	{
		TimerSubsystem->OnStartCountdown.AddDynamic(this, &ThisClass::OnCountdownStart);
		TimerSubsystem->OnFinishCountdown.AddDynamic(this, &ThisClass::OnCountdownEnd);
	}
	if(CalenderSubsystem)
	{
		CalenderSubsystem->OnDayStarted.AddDynamic(this, &ThisClass::StartDay);
		CalenderSubsystem->OnDayComplete.AddDynamic(this, &ThisClass::FinishDay);
	}
	if(!ResourceSubsystem)
	{
		UE_LOG(LogTemp, Error, TEXT("Resource Subsystem couldnt be initialised"));
	}
}

void AGameLevelMode::RequestForOrders_Implementation()
{
	
}


#pragma region Private methods
void AGameLevelMode::UpdateCalender()
{
	if(CalenderSubsystem)
	{
		if(CalenderSubsystem->GetCurrentDay() ==5)
		{
			CalenderSubsystem->UpdateWeek();
			CalenderSubsystem->ResetDays();
		}
		else
		{
			CalenderSubsystem->UpdateDay();
		}
	}
}
#pragma endregion

#pragma region Calender Bind methods

void AGameLevelMode::StartDay_Implementation()
{
	UpdateCalender();
	Execute_RequestForOrders(this);
}

void AGameLevelMode::FinishDay_Implementation(bool HasReached)
{
	if(HasReached)
	{
		TimerSubsystem->OnFinishCountdown.Broadcast();
	}
}

#pragma endregion

#pragma region PizzaSubsystem Bind Methods

void AGameLevelMode::OnReadyToTakeOrder_Implementation()
{
	StartDay();
}

void AGameLevelMode::OnOrderComplete_Implementation(int CustomerID, FPizzaStruct OrderSummary)
{
	ResourceSubsystem->AddBalance(ResourceToAdd);
}

void AGameLevelMode::OnAllOrdersComplete_Implementation()
{
	if(TimerSubsystem)
	{
		TimerSubsystem->OnStartCountdown.Broadcast(mCountdownDuration, mRate);
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
