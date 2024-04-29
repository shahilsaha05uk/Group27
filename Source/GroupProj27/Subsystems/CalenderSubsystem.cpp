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
	Super::Deinitialize();
}

void UCalenderSubsystem::UpdateCalender()
{
	if(CurrentDay >=5)	// if the Current Day is >=5
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
	OnDayComplete.Broadcast();	//Complete the Current Day
	UpdateCalender();	// Update the Calender
	OnDayStarted.Broadcast();	// Trigger the new day
}