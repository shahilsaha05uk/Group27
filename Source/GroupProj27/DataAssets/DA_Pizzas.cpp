// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_Pizzas.h"

void UDA_Pizzas::AddPizza(APizza* pizza)
{
	Count++;
	mPizzas.Add(Count, pizza);
	OnPizzaListAppended.Broadcast(pizza);
}

void UDA_Pizzas::RemovePizza(int id)
{
	if(mPizzas.Contains(id))
	{
		mPizzas.Remove(id);
		Count--;
	}
}
