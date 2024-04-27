// Fill out your copyright notice in the Description page of Project Settings.


#include "GameLevelMode.h"

#include "PizzaTimeGameState.h"


void AGameLevelMode::PostLogin(APlayerController* NewPlayer)
{
	mPizzaGameState = GetGameState<APizzaTimeGameState>();
	if(mPizzaGameState)
	{
		mPizzaGameState->OnMoneyStateUpdated.AddDynamic(this, &ThisClass::MakeDecisionBasedOnMoney);
	}
	Super::PostLogin(NewPlayer);

}

void AGameLevelMode::RequestForOrders_Implementation()
{
	
}

void AGameLevelMode::MakeDecisionBasedOnMoney_Implementation(int CurrentBalance)
{
	
}

