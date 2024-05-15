// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "DA_UIInputs.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJ27_API UDA_UIInputs : public UDataAsset
{
	GENERATED_BODY()

public:

	// UI Controls
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Inputs")
	UInputAction* IA_Pause;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Inputs")
	UInputAction* IA_OpenPhone;
};
