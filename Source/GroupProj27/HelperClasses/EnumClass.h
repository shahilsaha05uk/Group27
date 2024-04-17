// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumClass.generated.h"

UENUM()
enum EWidgetType
{
	MAIN_MENU, PAUSE_MENU, PLAYER_HUD, SETTINGS, CONTROLS_UI
};


UCLASS()
class GROUPPROJ27_API UEnumClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
};
