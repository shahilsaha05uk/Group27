// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_Pizzas.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPizzaListAppendSignature, class APizza*, pizza);

UCLASS(Blueprintable, BlueprintType)
class GROUPPROJ27_API UDA_Pizzas : public UDataAsset
{
	GENERATED_BODY()

private:

	UPROPERTY()
	int Count = -1;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPizzaListAppendSignature OnPizzaListAppended;
	

	UPROPERTY(EditDefaultsOnly)
	TMap<int, class APizza*> mPizzas;

	UFUNCTION(BlueprintCallable)
	void AddPizza(class APizza* pizza);
	UFUNCTION(BlueprintCallable)
	void RemovePizza(int id);
};
