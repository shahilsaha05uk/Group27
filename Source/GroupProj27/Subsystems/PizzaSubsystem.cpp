// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaSubsystem.h"

#pragma region Customer
void UPizzaSubsystem::AddCustomers(TMap<int, ACustomerMarker*> CustomerMap)
{
	if(!Customers.IsEmpty()) Customers.Empty(0);
	Customers = CustomerMap;
}

void UPizzaSubsystem::AddCustomer(int ID, ACustomerMarker* Customer)
{
	if(Customers.Contains(ID)) return;	// Check for duplicates
	Customers.Add(ID, Customer);
}

bool UPizzaSubsystem::RemoveCustomer(int ID)
{
	if(Customers.Contains(ID)) {
		Customers.Remove(ID);
		return true;
	}
	return false;
}
#pragma endregion

#pragma region Order
bool UPizzaSubsystem::CreateOrder(int CustomerID, FPizzaStruct order)
{
	if(Orders.Contains(CustomerID)) return false;
	
	if(Customers.Contains(CustomerID))
	{
		Orders.Add(CustomerID, order);
		OnOrderCreated.Broadcast(CustomerID);
	}
	return true;
}

bool UPizzaSubsystem::RemoveOrder(int CustomerID)
{
	if(!Orders.Contains(CustomerID)) return false;
	Orders.Remove(CustomerID);
	OnOrderComplete.Broadcast(CustomerID);
	return true;
}
#pragma endregion

#pragma region Quality Management
void UPizzaSubsystem::StartQualityTimer(float rate, int qualityDecreaseRate, bool bLoop)
{
	mQualityDecreaseRate = qualityDecreaseRate;
	GetWorld()->GetTimerManager().SetTimer(QualityTimerHandle, this, &UPizzaSubsystem::UpdateQuality, rate, bLoop);
}

void UPizzaSubsystem::StopQualityTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(QualityTimerHandle);
	QualityTimerHandle.Invalidate();
}

void UPizzaSubsystem::UpdateQuality()
{
	for (auto& o : Orders)
	{
		o.Value.Quality-=mQualityDecreaseRate;
	}
	OnQualityUpdated.Broadcast();
}
#pragma endregion

#pragma region Getters and Setters

FPizzaStruct UPizzaSubsystem::GetPizzaStatus(int CustomerID)
{
	return (Orders.Contains(CustomerID))? Orders[CustomerID]: FPizzaStruct();
}

ACustomerMarker* UPizzaSubsystem::GetCustomer(int ID)
{
	return (Customers.Find(ID))? Customers[ID] : nullptr;
}
#pragma endregion
