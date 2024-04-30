// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClockSubsystem.generated.h"


UENUM(BlueprintType)
enum EClockStatus
{
	TIMER_IDLE, TIMER_RUNNING, TIMER_INTERRUPTED, TIMER_FINISHED
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTimerSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentTimeSignature, FString, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopTimerSignature);    // when the timer is stopped by an entity
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedTimerSignature);    // when the timer automatically finishes

UCLASS()
class GROUPPROJ27_API UClockSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TEnumAsByte<EClockStatus> mClockStatus;
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCurrentTimeSignature CurrentTime;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FStartTimerSignature StartTimer;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FStopTimerSignature StopTimer;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FFinishedTimerSignature FinishTimer;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	EClockStatus GetClockStatus() {return mClockStatus;}
	UFUNCTION(BlueprintCallable)
	void SetClockStatus(EClockStatus status){mClockStatus = status;}
};
