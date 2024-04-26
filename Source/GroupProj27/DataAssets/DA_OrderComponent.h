// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "DA_OrderComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOrdersGeneratedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQualityUpdatedSignature, int, Quality);


UCLASS(Blueprintable, BlueprintType)
class GROUPPROJ27_API UDA_OrderComponent : public UDataAsset
{
	GENERATED_BODY()

private:

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<int, FPizzaStruct> Orders;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnOrdersGeneratedSignature OnOrdersGenerated;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnQualityUpdatedSignature OnQualityUpdated;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TMap<int, FPizzaStruct> GetOrders() {return Orders; }
	UFUNCTION(BlueprintCallable)
	void UpdateQuality(int ID);
	UFUNCTION(BlueprintCallable)
	void AddOrder(int id, FPizzaStruct order);
	UFUNCTION(BlueprintCallable)
	void RemoveOrder(FPizzaStruct& order, int ID);
};
