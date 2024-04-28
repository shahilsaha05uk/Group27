// Fill out your copyright notice in the Description page of Project Settings.


#include "CalenderSubsystem.h"

void UCalenderSubsystem::TriggerCalenderUpdate() const
{
	OnCalenderUpdated.Broadcast(CurrentWeek, CurrentDay);
}

void UCalenderSubsystem::Deinitialize()
{
	OnCalenderUpdated.Clear();
	OnDayStarted.Clear();
	OnDayComplete.Clear();
	OnStartCountdown.Clear();
	OnFinishCountdown.Clear();
	Super::Deinitialize();
}

void UCalenderSubsystem::UpdateCalender()
{
	if(CurrentDay >=1)	// if the Current Day is >=5
	{
		CurrentWeek++;
		CurrentDay = 1;
		OnWeekComplete.Broadcast();
	}
	else
	{
		CurrentDay++;
	}
	OnCalenderUpdated.Broadcast(CurrentWeek, CurrentDay);
}

void UCalenderSubsystem::StartDay()
{
	UpdateCalender();
	OnFinishCountdown.Broadcast();
	OnDayStarted.Broadcast();
}

void UCalenderSubsystem::EndDay(bool HasReachedShop)
{
	OnDayComplete.Broadcast(HasReachedShop);
}