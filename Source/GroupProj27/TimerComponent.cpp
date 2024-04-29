// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerComponent.h"

#include "Kismet/KismetStringLibrary.h"

void UTimerComponent::StartTimer(float Duration, float rate)
{
	mTotalduration = Duration;
	cTime = mTotalduration;
	mRate = rate;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::Timer, rate, true);
}

void UTimerComponent::StopTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	TimerHandle.Invalidate();
	OnTimerUpdate.Broadcast(UKismetStringLibrary::TimeSecondsToString(0.0f));
}

void UTimerComponent::Timer()
{
	cTime-= mRate;
	OnTimerUpdate.Broadcast(UKismetStringLibrary::TimeSecondsToString(cTime));

	if(cTime <=0.0f)
	{
		StopTimer();
	}
}

