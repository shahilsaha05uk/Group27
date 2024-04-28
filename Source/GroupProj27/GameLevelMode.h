// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HelperClasses/StructClass.h"
#include "Interfaces/PizzaModeInterface.h"
#include "GameLevelMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyStateUpdatedSignature, int, CurrentMoney);

UCLASS()
class GROUPPROJ27_API AGameLevelMode : public AGameModeBase, public IPizzaModeInterface
{
	GENERATED_BODY()

private:

public:
	UPROPERTY(EditDefaultsOnly)
	int mCountdownDuration;
	UPROPERTY(EditDefaultsOnly)
	float mRate;
	UPROPERTY(EditDefaultsOnly)
	int ResourceToAdd;
	UPROPERTY(BlueprintReadWrite)
	class UPizzaSubsystem* PizzaSubsystem;
	UPROPERTY(BlueprintReadWrite)
	class UTimerSubsystem* TimerSubsystem;
	UPROPERTY(BlueprintReadWrite)
	class UCalenderSubsystem* CalenderSubsystem;
	UPROPERTY(BlueprintReadWrite)
	class UResourceSubsystem* ResourceSubsystem;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMoneyStateUpdatedSignature OnMoneyStateUpdated;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TargetResourceThreshold = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TotalStrikes;

	virtual void OnPostLogin(AController* NewPlayer) override;

	// Pizza Subsystem methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnAllOrdersComplete();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnReadyToTakeOrder();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOrderComplete(int CustomerID, FPizzaStruct OrderSummary);

	// Timer Subsystem methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCountdownStart(float Duration, float Rate);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCountdownEnd();

	// Calender Subsystem methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartDay();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FinishDay(bool HasReached);

	// Interface methods
	virtual void RequestForOrders_Implementation() override;

	// Private Methods
	UFUNCTION(BlueprintCallable)
	void UpdateCalender();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MakeDecisionBasedOnMoney(int CurrentBalance);
};

