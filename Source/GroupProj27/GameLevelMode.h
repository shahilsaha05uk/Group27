// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HelperClasses/EnumClass.h"
#include "HelperClasses/StructClass.h"
#include "Interfaces/PizzaModeInterface.h"
#include "GameLevelMode.generated.h"

UCLASS()
class GROUPPROJ27_API AGameLevelMode : public AGameModeBase, public IPizzaModeInterface
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	class APizzaTimeGameState* mPizzaGameState;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TargetResourceThreshold = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int TotalStrikes;
	

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void RequestForOrders_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void MakeDecisionBasedOnMoney(int CurrentBalance);
};
