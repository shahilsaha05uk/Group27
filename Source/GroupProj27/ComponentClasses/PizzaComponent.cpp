// Fill out your copyright notice in the Description page of Project Settings.


#include "PizzaComponent.h"

#include "Algo/RandomShuffle.h"
#include "GroupProj27/Actors/CustomerMarker.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "GroupProj27/Subsystems/CustomerSubsystem.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UPizzaComponent::BeginPlay()
{
	TotalOrders = 0;
	mCustomerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCustomerSubsystem>();
	Super::BeginPlay();
}

#pragma region Order Management

bool UPizzaComponent::InitiateOrders_Implementation(bool AutoInitialise)
{
	if(mCustomerSubsystem)
	{
		mCustomerSubsystem->ClearAllOrders();

		const int RandOrderCount = UKismetMathLibrary::RandomIntegerInRange(mMinOrders, mMaxOrders);

		TArray<ACustomerMarker*> valArr;
		mCustomerSubsystem->GetAllCustomers().GenerateValueArray(valArr);

		Algo::RandomShuffle(valArr);
		TotalOrders = 0;
		for (int i = 0; i < RandOrderCount; i++)
		{
			FPizzaStruct pizzaStr;
			pizzaStr.DecreaseRate = mQualityDecreaseRate;
			pizzaStr.Quality = 100;
			CreateOrder(valArr[i]->GetID(), pizzaStr);

			TotalOrders++;
		}
		if(AutoInitialise) mCustomerSubsystem->OnOrderInitialised.Broadcast();

		return true;
	}
	return false;
}

bool UPizzaComponent::CreateOrder_Implementation(const FString& CustomerID, FPizzaStruct PizzaDetails)
{
	if(mCustomerSubsystem->GetOrderList().Contains(CustomerID)) return false;
	
	const FActorSpawnParameters params = FActorSpawnParameters();
	if(const auto Customer = mCustomerSubsystem->GetCustomer(CustomerID); Customer != nullptr)
	{
		Customer->Init(PizzaDetails);
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
	GetWorld()->GetTimerManager().SetTimer(QualityTimerHandle, this, &ThisClass::UpdateQuality, mQualityDecreaseRate, true, 0);
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