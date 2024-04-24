// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PizzaManager.generated.h"

UCLASS()
class GROUPPROJ27_API APizzaManager : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UPizza* mPizzas;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitiateOrders();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void AllocatePizza();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdatePizzas();
};
