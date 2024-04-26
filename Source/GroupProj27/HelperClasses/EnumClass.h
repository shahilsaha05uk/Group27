﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumClass.generated.h"

UENUM(BlueprintType)
enum EWidgetType
{
	MAIN_MENU, PAUSE_MENU, PLAYER_HUD, SETTINGS, CONTROLS_UI
};

UENUM(BlueprintType)
enum EGameDecision { LOSE, WIN, CONTINUE };

UCLASS()
class GROUPPROJ27_API UEnumClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};