// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_CalenderComponent.h"

void UDA_CalenderComponent::UpdateDay()
{
	CurrentDay++;
}

void UDA_CalenderComponent::ResetDays()
{
	CurrentDay = DefaultDay;
	CurrentWeek++;
}

