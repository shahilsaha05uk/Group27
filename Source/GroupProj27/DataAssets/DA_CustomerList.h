// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "DA_CustomerList.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQualityUpdatedSignature);

UCLASS(Blueprintable, BlueprintType)
class GROUPPROJ27_API UDA_CustomerList : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQualityUpdatedSignature OnQualityUpdated;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int, class ACustomerMarker*> Customers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int, FPizzaStruct> Orders;

	UFUNCTION(BlueprintCallable)
	void AddToOrderList(int OrderID, FPizzaStruct PizzaDetails);
	UFUNCTION(BlueprintCallable)
	void RemoveFromOrderList(int CustomerID);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRandomCustomerID();

};
