// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupProj27/HelperClasses/EnumClass.h"
#include "Shop.generated.h"

UCLASS()
class GROUPPROJ27_API AShop : public AActor
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float mCountdownDuration;
	UPROPERTY(EditDefaultsOnly)
	float mRate;

	UPROPERTY()
	bool bCountdownActivated;
	UPROPERTY()
	bool bHasPlayerArrived;
	UPROPERTY()
	class UPizzaSubsystem* mPizzaSubsystem;
	UPROPERTY()
	class UCalenderSubsystem* mCalenderSubsystem;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleShop(bool Activate);

	UFUNCTION(BlueprintCallable)
	void PlayerArrived();
	UFUNCTION(BlueprintCallable)
	void PlayerLeft();


	UFUNCTION(BlueprintCallable)
	void OnDayStarted();
	UFUNCTION(BlueprintCallable)
	void OnAllOrdersComplete();

	UFUNCTION(BlueprintCallable)
	void OnCountdownFinished();
};
