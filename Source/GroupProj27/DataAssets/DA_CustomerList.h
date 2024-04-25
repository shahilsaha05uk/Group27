// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_CustomerList.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GROUPPROJ27_API UDA_CustomerList : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int, class ACustomerMarker*> Customers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int, class ACustomerMarker*> Orders;

	UFUNCTION(BlueprintCallable)
	void AddToOrderList(int OrderID);
	UFUNCTION(BlueprintCallable)
	void RemoveFromOrderList(int CustomerID);

	UFUNCTION(BlueprintPure, BlueprintCallable)
	int GetRandomCustomerID();

};
