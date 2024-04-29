// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderCollectedSignature, int, ID, int, RemainingOrders);


UCLASS()
class GROUPPROJ27_API UCustomerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:

	UPROPERTY()
	class ACustomerManager* CustomerManager;
	UPROPERTY()
	TMap<int, class ACustomerMarker*> Customers;

	UPROPERTY()
	TMap<int, class APizza*> Orders;
public:
	UPROPERTY(BlueprintAssignable)
	FOnOrderCollectedSignature OnOrderCollected;
	UFUNCTION(BlueprintCallable)
	void OrderCollected(int ID);
	
	// Customer Management
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACustomerMarker* GetCustomer(int ID) {return (Customers.Find(ID))? Customers[ID] : nullptr;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TMap<int, class ACustomerMarker*> &GetAllCustomers() { return Customers; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleCustomer(int CustomerID, bool shouldActivate);

	UFUNCTION(BlueprintCallable)
	void RegisterCustomer(int ID, class ACustomerMarker* Customer)
	{
		if(!Customers.Contains(ID)) Customers.Add(ID, Customer);
	}
	
	// Order Mamangement
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<int, class APizza*> &GetOrderList() { return Orders; }
	UFUNCTION(BlueprintCallable)
	void UpdateOrders(const TMap<int, class APizza*>& OrderList) { Orders = OrderList; }
};
