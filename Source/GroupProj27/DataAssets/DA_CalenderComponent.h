// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CalenderComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeekUpdatedSignature, int, CurrentWeek);

UCLASS()
class GROUPPROJ27_API UDA_CalenderComponent : public UPrimaryDataAsset
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
	
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentDay() {return CurrentDay;}
	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentWeek() {return CurrentWeek; }
	
	UFUNCTION(BlueprintCallable)
	void UpdateDay();
	UFUNCTION(BlueprintCallable)
	void ResetDays();
};
