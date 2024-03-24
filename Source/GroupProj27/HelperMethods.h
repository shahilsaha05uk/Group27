// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructClass.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperMethods.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJ27_API UHelperMethods : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FBounds GetBounds(AActor* actor);
};
