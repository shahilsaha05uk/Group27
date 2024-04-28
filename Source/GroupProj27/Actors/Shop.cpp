// Fill out your copyright notice in the Description page of Project Settings.


#include "Shop.h"

#include "GroupProj27/Subsystems/CalenderSubsystem.h"
#include "GroupProj27/Subsystems/PizzaSubsystem.h"
#include "GroupProj27/Interfaces/PizzaModeInterface.h"
#include "GroupProj27/GameLevelMode.h"
#include <Kismet/KismetSystemLibrary.h>

void AShop::BeginPlay()
{
	Super::BeginPlay();

	const auto Instance = GetGameInstance();
	mPizzaSubsystem = Instance->GetSubsystem<UPizzaSubsystem>();
	mCalenderSubsystem = Instance->GetSubsystem<UCalenderSubsystem>();

	if(mPizzaSubsystem)
	{
		mPizzaSubsystem->OnAllOrdersComplete.AddDynamic(this, &ThisClass::OnAllOrdersComplete);
	}
	if(mCalenderSubsystem)
	{
		mCalenderSubsystem->OnDayStarted.AddDynamic(this, &ThisClass::OnDayStarted);
		mCalenderSubsystem->OnFinishCountdown.AddDynamic(this, &ThisClass::OnCountdownFinished);
	}
	ToggleShop(true);
}

#pragma region Private Methods

void AShop::ToggleShop_Implementation(bool Activate)
{

}

void AShop::PlayerArrived()
{
	bHasPlayerArrived = true;
	AGameLevelMode* gMode = Cast<AGameLevelMode>(GetWorld()->GetAuthGameMode());
	if (gMode)
	{
		IPizzaModeInterface::Execute_OnPlayerArrival(gMode, EPlayerArrivalStatus::ARRIVED);
	}
}

void AShop::PlayerLeft()
{
	bHasPlayerArrived = false;
}

#pragma endregion

#pragma region Calender subsystem Binded methods

void AShop::OnDayStarted()
{
	ToggleShop(false);
}

void AShop::OnCountdownFinished()
{
	bCountdownActivated = false;

	if (!bHasPlayerArrived && !bCountdownActivated)
	{
		AGameLevelMode* gMode = Cast<AGameLevelMode>(GetWorld()->GetAuthGameMode());
		if (gMode)
		{
			IPizzaModeInterface::Execute_OnPlayerArrival(gMode, EPlayerArrivalStatus::LATE);
		}
	}
}

#pragma endregion

#pragma region Pizza Subsystem Binded methods

void AShop::OnAllOrdersComplete()
{
	ToggleShop(true);
	bCountdownActivated = true;
	mCalenderSubsystem->StartCountdown(mCountdownDuration, mRate);
}

#pragma endregion




