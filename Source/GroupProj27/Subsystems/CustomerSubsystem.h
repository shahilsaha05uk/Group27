// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GroupProj27/Actors/CustomerMarker.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomerSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOrderCollectedSignature, FString, ID, int, RemainingOrders);
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
	TMap<FString, class ACustomerMarker*> Customers;

	UPROPERTY()
	TMap<FString, class ACustomerMarker*> Orders;
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnChefReviewGenerateSignature OnChefReviewGenerated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrderInitialisedSignature OnOrderInitialised;
	UPROPERTY(BlueprintAssignable)
	FOnOrderCollectedSignature OnOrderCollected;
	UFUNCTION(BlueprintCallable)
	void OrderCollected(const FString& ID);
	
	// Customer Management
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACustomerMarker* GetCustomer(const FString ID) {return (Customers.Find(ID))? Customers[ID] : nullptr;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TMap<FString, class ACustomerMarker*> &GetAllCustomers() { return Customers; }

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleCustomer(const FString& CustomerID, bool shouldActivate);

	UFUNCTION(BlueprintCallable)
	FString RegisterCustomer(class ACustomerMarker* Customer)
	{
		FGuid Guid = FGuid::NewGuid();
		FString ID = "Cust" + Guid.ToString();
		if(!Customers.Contains(ID))
		{
			Customers.Add(ID, Customer);
		}
		return ID;
	}
	
	// Order Mamangement
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const TMap<FString, class ACustomerMarker*> &GetOrderList() { return Orders; }
	UFUNCTION(BlueprintCallable)
	void AddOrder(FString ID, ACustomerMarker* Pizza)
	{
		if(Orders.Contains(ID)) return;
		Orders.Add(ID, Pizza);
	}
	UFUNCTION(BlueprintCallable)
	void ClearAllOrders()
	{
		if(!Orders.IsEmpty()) Orders.Empty(0);
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
	void UpdateOrders(const TMap<FString, class ACustomerMarker*>& OrderList) { Orders = OrderList; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACustomerMarker* GetOrderStatus(const FString& CustomerID)
	{
		return (Orders.Contains(CustomerID))? Orders[CustomerID]: nullptr;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool CanTakeOrders() { return Orders.IsEmpty(); }
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool HasOrders() { return Orders.Num() > 0; }
	UFUNCTION(BlueprintCallable)
	void RemoveOrderFromTheList(const FString& ID);
		
	UFUNCTION(BlueprintCallable)
	void UpdateCustomersForCollection();

	UFUNCTION(BlueprintCallable)
	void DealDamageToOrders(int damageVal);
};
