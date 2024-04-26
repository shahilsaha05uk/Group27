// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaManager.h"
#include "GroupProj27/DataAssets/DA_CustomerList.h"
#include "GroupProj27/DataAssets/DA_OrderComponent.h"

void APizzaManager::RequestOrder_Implementation()
{

}

void APizzaManager::InitiateOrders_Implementation()
{
	//TODO: Generate the order the list
}

void APizzaManager::UpdatePizzas_Implementation()
{

}

void APizzaManager::UpdateOrderList_Implementation(int id, FPizzaStruct order)
{
	mOrderList->AddOrder(id, order);
}

void APizzaManager::StartPizzaTimer_Implementation()
{
	
}
