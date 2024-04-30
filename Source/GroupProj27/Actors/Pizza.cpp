// Fill out your copyright notice in the Description page of Project Settings.


#include "Pizza.h"

#include "GroupProj27/PizzaComponent.h"


void APizza::BeginDestroy()
{
	Super::BeginDestroy();

	OnPizzaUpdated.RemoveAll(this);
}

void APizza::Init(UPizzaComponent* pComp, FPizzaStruct pDetails)
{
	PizzaDetails = pDetails;
	DecreaseRate = pDetails.DecreaseRate;
	mPizzaComp = pComp;
}

void APizza::UpdatePizza()
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
