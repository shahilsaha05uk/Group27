// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/BaseWidget.h"
#include "GameFramework/HUD.h"
#include "HelperClasses/EnumClass.h"
#include "GameHUD.generated.h"

UCLASS()
class GROUPPROJ27_API AGameHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<TEnumAsByte<EWidgetType>, UBaseWidget*> mWidgetInstances;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<TEnumAsByte<EWidgetType>, TSubclassOf<UBaseWidget>> mWidgetClassMap;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	class UBaseWidget* InitiateWidget(EWidgetType type);
	
};
