// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaManager.h"
#include "GroupProj27/DataAssets/DA_CustomerList.h"

void APizzaManager::RequestOrder_Implementation()
{

}

void APizzaManager::InitiateOrders_Implementation()
{
	//TODO: Generate the order the list
}

void APizzaManager::UpdatePizzas_Implementation()
{
	mCustomerList->OnQualityUpdated.Broadcast();
}