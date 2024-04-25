// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_Pizzas.h"

#include "GroupProj27/Actors/Pizza.h"

void UDA_Pizzas::AddPizza(APizza* pizza)
{
	Count++;
	pizza->Init(Count);
	mPizzas.Add(Count, pizza);

	OnPizzaListUpdated.Broadcast(pizza);
}

void UDA_Pizzas::RemovePizza(int id)
{
	if(mPizzas.Contains(id))
	{
		OnPizzaRemoved.Broadcast(id);
		mPizzas.Remove(id);
	}
}

void UDA_Pizzas::Initialise()
{
	// Clear out any entry from previous play if there is any entry present to allow the new ones
	Count = 0;
	if(mPizzas.IsEmpty()) return;
	for (auto p : mPizzas)
	{
		RemovePizza(p.Key);
	}
	mPizzas.Empty(0);
}
