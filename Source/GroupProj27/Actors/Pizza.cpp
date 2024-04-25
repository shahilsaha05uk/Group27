// Fill out your copyright notice in the Description page of Project Settings.


#include "Pizza.h"


void APizza::Init(int pizza_id)
{
	ID = pizza_id;
	GetWorld()->GetTimerManager().SetTimer(DegradeTimeHandler, this, &APizza::DegradeQuality, mRate, true);
}

void APizza::DegradeQuality()
{
	if(CurrentQuality > 0)
	{
		CurrentQuality-= mRate;

		OnQualityUpdateSignature.Broadcast(ID, CurrentQuality);
	}
	else
	{
		DegradeTimeHandler.Invalidate();
		GetWorld()->GetTimerManager().ClearTimer(DegradeTimeHandler);
	}
}
