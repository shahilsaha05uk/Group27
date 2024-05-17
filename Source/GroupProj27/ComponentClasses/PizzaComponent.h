// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PizzaComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class GROUPPROJ27_API UPizzaComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY()
	FTimerHandle QualityTimerHandle;
public:
	UPROPERTY(EditDefaultsOnly)
	int mMinOrders = 1;
	UPROPERTY(EditDefaultsOnly)
	int mMaxOrders = 5;
	UPROPERTY(BlueprintReadOnly)
	int TotalOrders = 0;
	UPROPERTY(BlueprintReadOnly)
	class UCustomerSubsystem* mCustomerSubsystem;

	UPROPERTY(EditDefaultsOnly)
	int mQualityDecreaseRate;

	virtual void BeginPlay() override;
	
	// Order Management
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool InitiateOrders(bool AutoInitialise);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool CreateOrder(const FString& CustomerID, FPizzaStruct PizzaDetails);
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void ClearOrders();

	// Quality Management
	UFUNCTION(BlueprintCallable)
	void StartQualityTimer();
	UFUNCTION(BlueprintCallable)
	void UpdateQuality();
	UFUNCTION(BlueprintCallable)
	void StopQualityTimer();
};
