// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GroupProj27/HelperClasses/EnumClass.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CalenderSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCalenderUpdatedSignature, int, Week, int, Day);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDayStartedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDayCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeekCompleteSignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStartCountdownTimerSignature, float, Duration, float, rate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFinishedCountdownTimerSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountdownStatusUpdateSignature, ECountdownStatus, Status);


UCLASS()
class GROUPPROJ27_API UCalenderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY()
	int CurrentDay = 0;
	UPROPERTY()
	int CurrentWeek = 0;

	UFUNCTION()
	void TriggerCalenderUpdate() const;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCalenderUpdatedSignature OnCalenderUpdated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDayStartedSignature OnDayStarted;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDayCompleteSignature OnDayComplete;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FStartCountdownTimerSignature OnStartCountdown;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCountdownStatusUpdateSignature OnCountdownUpdate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FFinishedCountdownTimerSignature OnFinishCountdown;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeekCompleteSignature OnWeekComplete;

	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentDay() {return CurrentDay;}
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentWeek() {return CurrentWeek; }
	
	UFUNCTION(BlueprintCallable)
	void UpdateCalender();
	UFUNCTION(BlueprintCallable)
	void StartDay();
	UFUNCTION(BlueprintCallable)
	void EndDay();

	UFUNCTION(BlueprintCallable)
	void StartCountdown(float Duration, float rate);
	UFUNCTION(BlueprintCallable)
	void EndCountdown();
};
