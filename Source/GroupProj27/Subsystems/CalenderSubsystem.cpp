// Fill out your copyright notice in the Description page of Project Settings.


#include "CalenderSubsystem.h"

void UCalenderSubsystem::Deinitialize()
{
	OnWeekUpdated.Clear();
	OnDayStarted.Clear();
	Super::Deinitialize();
}

void UCalenderSubsystem::StartDay()
{
	OnDayStarted.Broadcast();
}

void UCalenderSubsystem::UpdateDay()
{
	CurrentDay++;
}

void UCalenderSubsystem::ResetDays()
{
	CurrentDay = DefaultDay;
	CurrentWeek++;
}

