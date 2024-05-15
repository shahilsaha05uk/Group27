// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TimerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerValueUpdateSignature, FString, Time);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class GROUPPROJ27_API UTimerComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	FTimerHandle TimerHandle;
	
	UFUNCTION()
	void Timer();

	float cTime;
	float mTotalduration;
	float mRate;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTimerValueUpdateSignature OnTimerUpdate;
	
	UFUNCTION(BlueprintCallable)
	void StartTimer(float Duration, float rate);
	UFUNCTION(BlueprintCallable)
	void StopTimer();
};
