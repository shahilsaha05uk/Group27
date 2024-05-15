// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaComponent.h"

#include "GroupProj27/Actors/CustomerMarker.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "GroupProj27/Subsystems/CustomerSubsystem.h"

void UPizzaComponent::BeginPlay()
{
	mCustomerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCustomerSubsystem>();
	Super::BeginPlay();
}

#pragma region Order Management

bool UPizzaComponent::InitiateOrders_Implementation(bool AutoInitialise)
{
	return false;
}

bool UPizzaComponent::CreateOrder_Implementation(int CustomerID, FPizzaStruct PizzaDetails)
{
	if(mCustomerSubsystem->GetOrderList().Contains(CustomerID)) return false;
	
	const FActorSpawnParameters params = FActorSpawnParameters();
	if(const auto Customer = mCustomerSubsystem->GetCustomer(CustomerID); Customer != nullptr)
	{
		Customer->Init(this, PizzaDetails);
		mCustomerSubsystem->AddOrder(CustomerID, Customer);
		return true;
	}
	return false;
}
#pragma endregion

void UPizzaComponent::ClearOrders_Implementation()
{
	StopQualityTimer();
}

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
	auto &Orders = mCustomerSubsystem->GetOrderList();
	for (auto& o : Orders)
	{
		o.Value->UpdatePizza();
	}
}