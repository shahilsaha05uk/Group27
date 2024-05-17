// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PizzaTimeInstance.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJ27_API UPizzaTimeInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite)
	int CharacterID;
	
};
