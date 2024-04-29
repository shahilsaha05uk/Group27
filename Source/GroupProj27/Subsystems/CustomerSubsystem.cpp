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
	OnOrderCollected.Broadcast(ID, Orders.Num() -1);
}
