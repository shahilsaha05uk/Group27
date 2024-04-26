// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "PizzaManager.generated.h"

UCLASS()
class GROUPPROJ27_API APizzaManager : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDA_OrderComponent* mOrderList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDA_CustomerList* mCustomerList;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UDA_Pizzas* mPizzas;
	
	UPROPERTY(BlueprintReadWrite)
	FTimerHandle UpdateQualityTimerHandle;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void StartPizzaTimer();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void RequestOrder();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitiateOrders();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateOrderList(int id, FPizzaStruct order);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdatePizzas();
};
