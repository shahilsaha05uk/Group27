// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaSubsystem.h"

void UPizzaSubsystem::Deinitialize()
{
	OnAllOrdersComplete.Clear();
	OnOrderCreated.Clear();
	OnOrderComplete.Clear();
	OnQualityUpdated.Clear();
	Super::Deinitialize();
}


#pragma region Customer
void UPizzaSubsystem::AddCustomers(TMap<int, ACustomerMarker*> CustomerMap)
{
	if(!Customers.IsEmpty()) Customers.Empty(0);
	Customers = CustomerMap;
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

void UPizzaSubsystem::InitialiseOrder()
{
	OnOrderInitialised.Broadcast();
}

bool UPizzaSubsystem::OrderComplete(int CustomerID)
{
	if(!Orders.Contains(CustomerID)) return false;
	const auto order = Orders[CustomerID];

	OnOrderComplete.Broadcast(CustomerID, order);
	Orders.Remove(CustomerID);
	
	if(Orders.IsEmpty())
	{
		OnAllOrdersComplete.Broadcast();
	}
	return true;
}


#pragma endregion

#pragma region Quality Management
void UPizzaSubsystem::StartQualityTimer(float rate, int qualityDecreaseRate, bool bLoop)
{
	if (QualityTimerHandle.IsValid()) return;
	mQualityDecreaseRate = qualityDecreaseRate;
	GetWorld()->GetTimerManager().SetTimer(QualityTimerHandle, this, &UPizzaSubsystem::UpdateQuality, rate, bLoop);
}

void UPizzaSubsystem::FinishedQualityTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(QualityTimerHandle);
	QualityTimerHandle.Invalidate();
}

void UPizzaSubsystem::UpdateQuality()
{
	for (auto& o : Orders)
	{
		int &quality = o.Value.Quality;
		FString &review = o.Value.Review; 
		quality-=mQualityDecreaseRate;

		//TODO: Improve this condition
		if(quality >= 70) review = "Perfect!!";
		else if(quality >= 40 && quality <70) review = "Good!!";
		else if(quality >= 10 && quality <40) review = "Average!!";
		else review = "POOP!!!";
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
