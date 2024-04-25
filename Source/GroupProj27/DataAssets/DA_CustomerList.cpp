// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_CustomerList.h"

void UDA_CustomerList::AddToOrderList(int OrderID, FPizzaStruct PizzaDetails)
{
	// Remove from Customers
	if(Customers.Contains(OrderID))
	{
		Orders.Add(OrderID, PizzaDetails);
		Customers.Remove(OrderID);
	}
}

void UDA_CustomerList::RemoveFromOrderList(int CustomerID)
{
	//Remove from the Orders
	if(Orders.Contains(CustomerID))
	{
		const auto Cust = Orders[CustomerID].Customer;
		Customers.Add(CustomerID, Cust);
		Orders.Remove(CustomerID);
	}
}

int UDA_CustomerList::GetRandomCustomerID()
{
	return FMath::RandRange(0, Customers.Num() - 1);
}
