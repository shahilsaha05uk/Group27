// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJ27_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// template methods
	template <typename T, typename = std::enable_if_t<std::is_base_of_v<UBaseWidget, T>>>
	T* GetWidgetAs()
	{
		return Cast<T>(this);
	};

};

