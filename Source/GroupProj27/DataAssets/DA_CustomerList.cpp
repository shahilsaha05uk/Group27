// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_CustomerList.h"

void UDA_CustomerList::AddToOrderList(int OrderID)
{
	// Remove from Customers
	if(Customers.Contains(OrderID))
	{
		Orders.Add(OrderID);
		Customers.Remove(OrderID);
	}
}

void UDA_CustomerList::RemoveFromOrderList(int CustomerID)
{
	//Remove from the Orders
	if(Orders.Contains(CustomerID))
	{
		Customers.Add(CustomerID);
		Orders.Remove(CustomerID);
	}
}

int UDA_CustomerList::GetRandomCustomerID()
{
	return FMath::RandRange(0, Customers.Num() - 1);
}
