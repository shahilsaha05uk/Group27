// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaComponent.h"

#include "Actors/CustomerMarker.h"
#include "HelperClasses/StructClass.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/CustomerSubsystem.h"

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

/*
bool UPizzaComponent::CreateOrder(int CustomerID)
{
	if(mCustomerSubsystem->GetOrderList().Contains(CustomerID)) return false;

	auto c = UKismetArrayLibrary::Array_Random(mCustomerSubsystem->GetAllCustomers().
	if(const auto Customer = mCustomerSubsystem->GetCustomer(CustomerID); Customer != nullptr)
	{
		Customer->Init(this, FPizzaStruct({CustomerID, 100, 1, ""}));
		mCustomerSubsystem->AddOrder(CustomerID, Customer);
		return true;
	}
	return false;
}
*/
bool UPizzaComponent::CreateOrder_Implementation(int CustomerID)
{
	return false;
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
	auto &Orders = mCustomerSubsystem->GetOrderList();
	for (auto& o : Orders)
	{
		o.Value->UpdatePizza();
	}
}