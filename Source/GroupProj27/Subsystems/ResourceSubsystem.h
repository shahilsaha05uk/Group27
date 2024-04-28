// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ResourceSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentBalanceUpdateSignature, int, CurentBalance);
UCLASS(BlueprintType, Blueprintable)
class GROUPPROJ27_API UResourceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	UPROPERTY()
	int mCurrentResource;
	
public:

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnCurrentBalanceUpdateSignature OnBalanceUpdate;

	virtual void Deinitialize() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Public")
	int mStartingResource;

	UFUNCTION(BlueprintPure)
	int GetCurrentBalance(){return mCurrentResource;}
	UFUNCTION(BlueprintCallable)
	void AddBalance(int increaseBy);
	UFUNCTION(BlueprintCallable)
	void DeductBalance(int decreaseBy);

};
