// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerMarker.h"

#include "GroupProj27/Subsystems/CustomerSubsystem.h"

void ACustomerMarker::BeginPlay()
{
	CustomerSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UCustomerSubsystem>();
	Super::BeginPlay();
}

void ACustomerMarker::BeginDestroy()
{
	OnPizzaUpdated.RemoveAll(this);
	Super::BeginDestroy();
}


void ACustomerMarker::ToggleCustomer_Implementation(bool Value)
{
	bChosenForOrderList = false;
	CustomerSubsystem->OnOrderInitialised.RemoveAll(this);
}

void ACustomerMarker::CollectPizza_Implementation()
{
}

void ACustomerMarker::OnInitialisedForOrder()
{
	if(bChosenForOrderList)
	{
		ToggleCustomer(true);
		CustomerSubsystem->OnOrderInitialised.RemoveAll(this);
	}
}

void ACustomerMarker::Init(UPizzaComponent* pComp, FPizzaStruct pDetails)
{
	PizzaDetails = pDetails;
	DecreaseRate = pDetails.DecreaseRate;
	mPizzaComp = pComp;
	bChosenForOrderList = true;
	CustomerSubsystem->OnOrderInitialised.AddDynamic(this, &ThisClass::OnInitialisedForOrder);
}

void ACustomerMarker::UpdatePizza()
{
	FString &review = PizzaDetails.Review;
	int &CurrentQuality = PizzaDetails.Quality;

	// Update the Current Quality
	CurrentQuality -= DecreaseRate;

	// Update the Current Review
	if(CurrentQuality >= 70) review = "Perfect!!";
	else if(CurrentQuality >= 40 && CurrentQuality <70) review = "Good!!";
	else if(CurrentQuality >= 10 && CurrentQuality <40) review = "Average!!";
	else review = "POOP!!!";
	
	OnPizzaUpdated.Broadcast(PizzaDetails);
}

void ACustomerMarker::TakeQualityDamage_Implementation()
{
	int &CurrentQuality = PizzaDetails.Quality;
	int &Damage = PizzaDetails.DamageRate;

	CurrentQuality-= Damage;
	OnPizzaUpdated.Broadcast(PizzaDetails);
}

void ACustomerMarker::AddQuality_Implementation(int increaseBy)
{
	int &CurrentQuality = PizzaDetails.Quality;
	CurrentQuality += increaseBy;

	OnPizzaUpdated.Broadcast(PizzaDetails);
}