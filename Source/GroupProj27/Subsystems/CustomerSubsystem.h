// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderCollectedSignature, int, ID, int, RemainingOrders);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOrderInitialisedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChefReviewGenerateSignature, int, AverageReview);
UCLASS()
class GROUPPROJ27_API UCustomerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

private:
	int IDCount = -1;
	
	UPROPERTY()
	class ACustomerManager* CustomerManager;
	UPROPERTY()
	TMap<int, class ACustomerMarker*> Customers;

	UPROPERTY()
	TMap<int, class ACustomerMarker*> Orders;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnChefReviewGenerateSignature OnChefReviewGenerated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderInitialisedSignature OnOrderInitialised;
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
	int RegisterCustomer(class ACustomerMarker* Customer)
	{
		IDCount++;
		if(!Customers.Contains(IDCount))
		{
			Customers.Add(IDCount, Customer);
		}
		return IDCount;
	}
	
	// Order Mamangement
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<int, class ACustomerMarker*> &GetOrderList() { return Orders; }
	UFUNCTION(BlueprintCallable)
	void AddOrder(int ID, ACustomerMarker* Pizza)
	{
		if(Orders.Contains(ID)) return;
		Orders.Add(ID, Pizza);
	}
	UFUNCTION(BlueprintCallable)
	void FlushEverything()
	{
		if(!Orders.IsEmpty())
			Orders.Empty(0);

		for (auto c : Customers)
		{
			Customers.Remove(c.Key);
		}
		IDCount = -1;
	}
	UFUNCTION(BlueprintCallable)
	void UpdateOrders(const TMap<int, class ACustomerMarker*>& OrderList) { Orders = OrderList; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACustomerMarker* GetOrderStatus(int CustomerID)
	{
		return (Orders.Contains(CustomerID))? Orders[CustomerID]: nullptr;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanTakeOrders() { return Orders.IsEmpty(); }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasOrders() { return Orders.Num() > 0; }
	UFUNCTION(BlueprintCallable)
	void RemoveOrderFromTheList(int ID);
		
	UFUNCTION(BlueprintCallable)
	void UpdateCustomersForCollection();

	UFUNCTION(BlueprintCallable)
	void DealDamageToOrders(int damageVal);
};
