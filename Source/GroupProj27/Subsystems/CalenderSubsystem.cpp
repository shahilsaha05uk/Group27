// Fill out your copyright notice in the Description page of Project Settings.


#include "CalenderSubsystem.h"

void UCalenderSubsystem::UpdateDay()
{
	CurrentDay++;
}

void UCalenderSubsystem::ResetDays()
{
	CurrentDay = DefaultDay;
	CurrentWeek++;
}

