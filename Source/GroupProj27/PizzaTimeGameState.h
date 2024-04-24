// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HelperClasses/EnumClass.h"
#include "PizzaTimeGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateProcessedSignature, EGameDecision, decision);

UCLASS()
class GROUPPROJ27_API APizzaTimeGameState : public AGameStateBase
{
	GENERATED_BODY()

private:

	UPROPERTY()
	int CurrentStrikes;

public:

	UPROPERTY(EditDefaultsOnly)
	int TargetResourceThreshold = 1000;
	UPROPERTY(EditDefaultsOnly)
	int TotalStrikes;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnGameStateProcessedSignature OnGameStateProcessed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDA_ResourceComponent* mResourcesComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDA_CalenderComponent* mCalenderComp;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnWeekUpdated(int CurrentWeek);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetCurrentStrikes() {return CurrentStrikes;}
};
