// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HelperClasses/EnumClass.h"
#include "GameLevelMode.generated.h"

UCLASS()
class GROUPPROJ27_API AGameLevelMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Decision(EGameDecision gDecision);
};
