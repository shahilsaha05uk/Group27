// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "CustomerMarker.generated.h"

// This is to update the Pizza details
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdatePizzaSignature, FPizzaStruct, pStruct);

UCLASS()
class GROUPPROJ27_API ACustomerMarker : public AActor
{
	GENERATED_BODY()


private:
	UPROPERTY()
	int ID;
	UPROPERTY()
	int DecreaseRate;
	UPROPERTY()
	FPizzaStruct PizzaDetails;
	UPROPERTY()
	class UPizzaComponent* mPizzaComp;

	UPROPERTY()
	FTimerHandle DegradeTimeHandler;

public:
	UPROPERTY(BlueprintReadOnly)
	class UCustomerSubsystem* CustomerSubsystem;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnUpdatePizzaSignature OnPizzaUpdated;

	UPROPERTY(BlueprintReadWrite)
	bool bChosenForOrderList;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FPizzaStruct GetDetails() {return PizzaDetails;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetID(){return ID;}

	UFUNCTION(BlueprintCallable)
	void OnInitialisedForOrder();
	UFUNCTION(BlueprintCallable)
	void Init(class UPizzaComponent* pComp, FPizzaStruct pDetails);
	UFUNCTION(BlueprintCallable)
	void UpdatePizza();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddQuality(int increaseBy);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeductQuality(int decreaseBy);
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCustomerStruct mCustomerDetails;
	
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CollectPizza();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ToggleCustomer(bool Value);
};
