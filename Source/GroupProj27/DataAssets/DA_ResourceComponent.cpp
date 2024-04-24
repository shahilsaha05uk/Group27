// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_ResourceComponent.h"

void UDA_ResourceComponent::AddBalance(int increaseBy)
{
	mCurrentResource += increaseBy;
	OnBalanceUpdate.Broadcast(mCurrentResource);
}

void UDA_ResourceComponent::DeductBalance(int decreaseBy)
{
	mCurrentResource -= decreaseBy;
	OnBalanceUpdate.Broadcast(mCurrentResource);
}
