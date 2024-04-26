// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "DA_CustomerList.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GROUPPROJ27_API UDA_CustomerList : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<int, class ACustomerMarker*> Customers;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ACustomerMarker* GetRandomCustomer(int &ID);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetRandomCustomerID();

};
