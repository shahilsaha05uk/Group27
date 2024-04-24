// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ClimbInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UClimbInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GROUPPROJ27_API IClimbInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

		
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Hang(bool isLedgeDetected);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopHamg();

};
