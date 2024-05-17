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
	int DecreaseRate;
	UPROPERTY()
	FPizzaStruct PizzaDetails;
	UPROPERTY()
	FTimerHandle DegradeTimeHandler;

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<TEnumAsByte<EPizzaQuality>, FMinMaxStruct> QualityRange;
	UPROPERTY(BlueprintReadWrite)
	FString ID;
	UPROPERTY(BlueprintReadOnly)
	class UCustomerSubsystem* CustomerSubsystem;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnUpdatePizzaSignature OnPizzaUpdated;

	UPROPERTY(BlueprintReadWrite)
	bool bChosenForOrderList;

	UPROPERTY(BlueprintReadWrite)
	bool bIsActivated;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USphereComponent* mCollider;

	ACustomerMarker();
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
	
	UFUNCTION(BlueprintCallable)
	void OnColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FPizzaStruct GetDetails() {return PizzaDetails;}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FString GetID(){return ID;}

	UFUNCTION(BlueprintCallable)
	void OnInitialisedForOrder();
	UFUNCTION(BlueprintCallable)
	void Init(FPizzaStruct pDetails);
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
