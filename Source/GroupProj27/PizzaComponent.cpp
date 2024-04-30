// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaComponent.h"

#include "CustomerManager.h"
#include "Actors/Pizza.h"
#include "HelperClasses/StructClass.h"
#include "Subsystems/CustomerSubsystem.h"

void UPizzaComponent::BeginPlay()
{
	mCustomerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCustomerSubsystem>();
	if(mCustomerSubsystem)
	{
		mCustomerSubsystem->OnOrderCollected.AddDynamic(this, &ThisClass::OrderComplete);
	}
	Super::BeginPlay();
}

#pragma region Order Management

bool UPizzaComponent::InitiateOrders_Implementation()
{
	return false;
}

bool UPizzaComponent::CreateOrder(int CustomerID)
{
	if(Orders.Contains(CustomerID)) return false;
	
	const FActorSpawnParameters params = FActorSpawnParameters();
	if(mCustomerSubsystem->GetCustomer(CustomerID))
	{
		// Activate the Customer
		mCustomerSubsystem->ToggleCustomer(CustomerID, true);

		// Make the Pizza Actor for that Customer
		const auto pizza = GetWorld()->SpawnActor<APizza>(FVector::Zero(), FRotator::ZeroRotator, params);
		pizza->Init(this, FPizzaStruct({CustomerID, 100, 1, ""}));
		Orders.Add(CustomerID, pizza);
		return true;
	}
	return false;
}

void UPizzaComponent::OrderComplete_Implementation(int CustomerID, int RemainingOrders)
{
	if(!Orders.Contains(CustomerID)) return;
	Orders.Remove(CustomerID);
	mCustomerSubsystem->UpdateOrders(Orders);
	if(Orders.IsEmpty())
	{
		StopQualityTimer();
	}
}

#pragma endregion

void UPizzaComponent::StartQualityTimer()
{
	GetWorld()->GetTimerManager().SetTimer(QualityTimerHandle, this, &ThisClass::UpdateQuality, mQualityDecreaseRate, true);
}

void UPizzaComponent::StopQualityTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(QualityTimerHandle);
	QualityTimerHandle.Invalidate();
}
void UPizzaComponent::UpdateQuality()
{
	for (auto& o : Orders)
	{
		o.Value->UpdatePizza();
	}
}