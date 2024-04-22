// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"

UBaseWidget* AGameHUD::InitiateWidget_Implementation(EWidgetType type)
{
	const TSubclassOf<UBaseWidget> widgetClass = mWidgetClassMap[type];
	if(!widgetClass) return nullptr;
	
	return CreateWidget<UBaseWidget>(GetOwningPlayerController(), widgetClass);
}
