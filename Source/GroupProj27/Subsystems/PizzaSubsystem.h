// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "Subsystems/WorldSubsystem.h"
#include "PizzaSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualityUpdatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderCreateSignature, int, CustomerID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderCompleteSignature, int, CustomerID);

UCLASS()
class GROUPPROJ27_API UPizzaSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TMap<int, class ACustomerMarker*> Customers;
	UPROPERTY()
	TMap<int, FPizzaStruct> Orders;
	UPROPERTY()
	int mQualityDecreaseRate;
public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderCreateSignature OnOrderCreated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderCompleteSignature OnOrderComplete;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQualityUpdatedSignature OnQualityUpdated;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle QualityTimerHandle;

	// Customer Management
	UFUNCTION(BlueprintCallable)
	void AddCustomers(TMap<int, class ACustomerMarker*> CustomerMap);
	UFUNCTION(BlueprintCallable)
	void AddCustomer(int ID, class ACustomerMarker* Customer);
	UFUNCTION(BlueprintCallable)
	bool RemoveCustomer(int ID);

	// Order Management
	UFUNCTION(BlueprintCallable)
	bool CreateOrder(int CustomerID, FPizzaStruct order);
	UFUNCTION(BlueprintCallable)
	bool RemoveOrder(int CustomerID);

	// Quality Management
	UFUNCTION(BlueprintCallable)
	void StartQualityTimer(float rate, int qualityDecreaseRate, bool bLoop);
	UFUNCTION(BlueprintCallable)
	void StopQualityTimer();
	UFUNCTION(BlueprintCallable)
	void UpdateQuality();

	// Getters and Setters
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FPizzaStruct GetPizzaStatus(int CustomerID);

	// Debugs ONLY
	UFUNCTION(BlueprintCallable, BlueprintPure)
	class ACustomerMarker* GetCustomer(int ID);
};
