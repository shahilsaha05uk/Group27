// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_OrderComponent.h"

void UDA_OrderComponent::UpdateQuality(int ID)
{
	if(Orders.Contains(ID))
	{
		auto& o = Orders[ID];
		o.Quality-=1;

		OnQualityUpdated.Broadcast(o.Quality);
	}
}

void UDA_OrderComponent::AddOrder(int id, FPizzaStruct order)
{
	if(!Orders.Contains(id)) Orders.Add(id, order);
}

void UDA_OrderComponent::RemoveOrder(FPizzaStruct& order, int ID)
{
	if(Orders.Contains(ID))
	{
		order = Orders[ID];
		Orders.Remove(ID);
	}
}