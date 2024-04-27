// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "HelperClasses/EnumClass.h"
#include "HelperClasses/StructClass.h"
#include "PizzaTimeGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoneyStateUpdatedSignature, int, CurrentMoney);

UCLASS()
class GROUPPROJ27_API APizzaTimeGameState : public AGameStateBase
{
	GENERATED_BODY()

private:

	UPROPERTY()
	int CurrentStrikes;

public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnMoneyStateUpdatedSignature OnMoneyStateUpdated;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UPizzaSubsystem* mPizzaSubsystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UCalenderSubsystem* CalenderSubsystem;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UResourceSubsystem* mResourceSubsystem;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnMoneyUpdated(int CurentBalance);
};
