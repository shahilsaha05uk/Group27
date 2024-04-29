// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PizzaSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReadyToTakeOrderSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualityUpdatedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllOrdersCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOrderCreateSignature, int, CustomerID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOrderInitialisedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderCompleteSignature, int, CustomerID, FPizzaStruct, OrderSummary);

UCLASS()
class GROUPPROJ27_API UPizzaSubsystem : public UGameInstanceSubsystem
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

	virtual void Deinitialize() override;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnReadyToTakeOrderSignature OnReadyToTakeOrder;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAllOrdersCompleteSignature OnAllOrdersComplete;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderCreateSignature OnOrderCreated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderInitialisedSignature OnOrderInitialised;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderCompleteSignature OnOrderComplete;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQualityUpdatedSignature OnQualityUpdated;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle QualityTimerHandle;

	// Customer Management
	UFUNCTION(BlueprintCallable)
	void AddCustomers(TMap<int, class ACustomerMarker*> CustomerMap);

	// Order Management
	UFUNCTION(BlueprintCallable)
	bool CreateOrder(int CustomerID, FPizzaStruct order);
	UFUNCTION(BlueprintCallable)
	void InitialiseOrder();
	UFUNCTION(BlueprintCallable)
	bool OrderComplete(int CustomerID);

	// Quality Management
	UFUNCTION(BlueprintCallable)
	void StartQualityTimer(float rate, int qualityDecreaseRate, bool bLoop);
	UFUNCTION(BlueprintCallable)
	void FinishedQualityTimer();
	UFUNCTION(BlueprintCallable)
	void UpdateQuality();

	// Getters and Setters
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanTakeOrders() { return Orders.IsEmpty(); }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FPizzaStruct GetPizzaStatus(int CustomerID);

	// Debugs ONLY
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACustomerMarker* GetCustomer(int ID);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TMap<int, FPizzaStruct> GetOrders() {return Orders;}
};
