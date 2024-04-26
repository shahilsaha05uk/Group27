// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_CustomerList.h"

ACustomerMarker* UDA_CustomerList::GetRandomCustomer(int& ID)
{
	ID = GetRandomCustomerID();
	return Customers[ID];
}

int UDA_CustomerList::GetRandomCustomerID()
{
	
	return FMath::RandRange(0, Customers.Num() - 1);
}
