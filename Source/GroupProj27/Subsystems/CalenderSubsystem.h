// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CalenderSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeekUpdatedSignature, int, CurrentWeek);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDayStartedSignature);

UCLASS()
class GROUPPROJ27_API UCalenderSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
private:

	UPROPERTY()
	int DefaultDay = 1;
	UPROPERTY()
	int DefaultWeek = 1;

	
	UPROPERTY()
	int CurrentDay = 0;
	UPROPERTY()
	int CurrentWeek = 0;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeekUpdatedSignature OnWeekUpdated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDayStartedSignature OnDayStarted;
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentDay() {return CurrentDay;}
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentWeek() {return CurrentWeek; }
	
	UFUNCTION(BlueprintCallable)
	void StartDay();
	UFUNCTION(BlueprintCallable)
	void UpdateDay();
	UFUNCTION(BlueprintCallable)
	void ResetDays();

};
