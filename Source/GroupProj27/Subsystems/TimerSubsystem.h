// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartCountdownTimerSignature, float, Duration, float, rate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedCountdownTimerSignature);

UCLASS()
class GROUPPROJ27_API UTimerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FStartCountdownTimerSignature OnStartCountdown;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FFinishedCountdownTimerSignature OnFinishCountdown;
	
};
