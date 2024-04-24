// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pizza.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQualityUpdateSignature, int, id, int, quality);

UCLASS()
class GROUPPROJ27_API APizza : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int ID;
	UPROPERTY()
	int CurrentQuality = 100;

	UPROPERTY()
	FTimerHandle DegradeTimeHandler;

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQualityUpdateSignature OnQualityUpdateSignature;
	
	UPROPERTY(EditDefaultsOnly)
	const int mInterval = 3000;	// the interval before the next degrade
	UPROPERTY(EditDefaultsOnly)
	const int mRate = 1;	// the rate at which the quality will decrease
	
	UFUNCTION(BlueprintCallable)
	void Init(int id);
	UFUNCTION(BlueprintCallable)
	void DegradeQuality();
};
