// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ClockSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartTimerSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentTimeSignature, FString, CurrentTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopTimerSignature);
UCLASS()
class GROUPPROJ27_API UClockSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCurrentTimeSignature CurrentTime;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FStartTimerSignature StartTimer;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FStopTimerSignature StopTimer;
	
};
