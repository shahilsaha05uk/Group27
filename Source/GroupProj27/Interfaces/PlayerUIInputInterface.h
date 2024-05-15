// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerUIInputInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlayerUIInputInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GROUPPROJ27_API IPlayerUIInputInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void PauseGame();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TogglePhone();
	
};
