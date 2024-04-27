// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/PizzaModeInterface.h"
#include "GameLevelMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyStateUpdatedSignature, int, CurrentMoney);

UCLASS()
class GROUPPROJ27_API AGameLevelMode : public AGameModeBase, public IPizzaModeInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMoneyStateUpdatedSignature OnMoneyStateUpdated;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TargetResourceThreshold = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TotalStrikes;
	

	virtual void RequestForOrders_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MakeDecisionBasedOnMoney(int CurrentBalance);
};
