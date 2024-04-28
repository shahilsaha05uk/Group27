// Fill out your copyright notice in the Description page of Project Settings.


#include "CalenderSubsystem.h"

void UCalenderSubsystem::TriggerCalenderUpdate() const
{
	OnCalenderUpdated.Broadcast(CurrentWeek, CurrentDay);
}

void UCalenderSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UCalenderSubsystem::StartDay()
{
	OnDayStarted.Broadcast();
	TriggerCalenderUpdate();
}

void UCalenderSubsystem::UpdateDay()
{
	CurrentDay++;
	TriggerCalenderUpdate();
}

void UCalenderSubsystem::UpdateWeek()
{
	CurrentWeek++;
	TriggerCalenderUpdate();
}

void UCalenderSubsystem::ResetDays()
{
	CurrentDay = DefaultDay;
	TriggerCalenderUpdate();
}

