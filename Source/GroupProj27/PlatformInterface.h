// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlatformInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class UPlatformInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GROUPPROJ27_API IPlatformInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<AActor*> GetLedges();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetClosestLedge();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartTrackingPlayer(AActor* playerRef);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopTrackingPlayer();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateBuildingLedgeAvailability(AActor* PlayerRef);
};
