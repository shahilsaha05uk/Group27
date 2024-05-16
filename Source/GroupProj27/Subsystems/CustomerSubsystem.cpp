// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerSubsystem.h"

#include "GroupProj27/Actors/CustomerMarker.h"

void UCustomerSubsystem::ToggleCustomer_Implementation(int CustomerID, bool shouldActivate)
{
	if(const auto Customer = GetCustomer(CustomerID); Customer != nullptr) {
		Customer->ToggleCustomer(shouldActivate);
	}
}
void UCustomerSubsystem::OrderCollected(int ID)
{
	const auto& CustomerRef = Orders[ID];
	if(CustomerRef != nullptr)
	{
		CustomerRef->ToggleCustomer(false);
		OnOrderCollected.Broadcast(ID, Orders.Num());
	}
}

void UCustomerSubsystem::RemoveOrderFromTheList(int ID)
{
	const auto& CustomerRef = Orders[ID];
	if(CustomerRef != nullptr)
	{
		Orders.Remove(ID);
	}
}

void UCustomerSubsystem::UpdateCustomersForCollection()
{
	for (auto o : Orders)
	{
		int id = o.Value->GetID();

		if(Customers.Contains(id))
		{
			Customers[id]->ToggleCustomer(true);
		}
	}
}

void UCustomerSubsystem::DealDamageToOrders(int damageVal)
{
	if(Orders.IsEmpty()) return;

	for (auto o : Orders)
	{
		o.Value->DeductQuality(damageVal);
	}
}
