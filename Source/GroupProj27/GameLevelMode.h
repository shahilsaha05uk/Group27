// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HelperClasses/EnumClass.h"
#include "HelperClasses/StructClass.h"
#include "Interfaces/PizzaModeInterface.h"
#include "Subsystems/ResourceSubsystem.h"
#include "GameLevelMode.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatusUpdateSignature, EPlayerArrivalStatus, PlayerStatus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDecisionMade, EGameDecision, Decision);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStrikesUpdated, int, Strikes);

UCLASS()
class GROUPPROJ27_API AGameLevelMode : public AGameModeBase, public IPizzaModeInterface
{
	GENERATED_BODY()

private:

	UPROPERTY()
	int CurrentStrikes = 0;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Private")
	int mCountdownDuration;
	UPROPERTY(EditDefaultsOnly, Category = "Private")
	float mRate;
	UPROPERTY(EditDefaultsOnly, Category = "Private")
	int ResourceToAdd;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	int TargetResourceThreshold = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	int TotalStrikes;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	int mStartingBalance;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Private")
	bool bHasReached;


	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlayerStatusUpdateSignature OnPlayerStatusUpdate;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDecisionMade OnDecisionMade;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStrikesUpdated OnStrikesUpdated;
	
	UPROPERTY(BlueprintReadWrite)
	class UPizzaSubsystem* PizzaSubsystem;
	UPROPERTY(BlueprintReadWrite)
	class UCalenderSubsystem* CalenderSubsystem;
	UPROPERTY(BlueprintReadWrite)
	class UResourceSubsystem* ResourceSubsystem;

	virtual void OnPostLogin(AController* NewPlayer) override;

	// Pizza Subsystem methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnOrderComplete(int CustomerID, FPizzaStruct OrderSummary);

	// Calender Subsystem methods
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDayStart();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnWeekComplete();

	// Interface methods
	virtual void RequestForOrders_Implementation() override;
	virtual void OnPlayerStatusUpdated_Implementation(EPlayerArrivalStatus PlayerStatus) override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPlayerIsLate(bool bHasArrived);
	// Private Methods
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasEnoughBalanceToPayRent() {return ResourceSubsystem->GetCurrentBalance() > TargetResourceThreshold; }
};

