// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/OverlaySlot.h" // Include necessary headers for UOverlaySlot
#include "Widgets/SOverlay.h" // Include necessary headers for SOverlay

#include "BaseWidget.generated.h"


UCLASS()
class GROUPPROJ27_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void SetOverlayAlignment(class UOverlaySlot* OverlayWidgetRef ,EHorizontalAlignment hAlignment, EVerticalAlignment vAlignment);
	UFUNCTION(BlueprintCallable)
	void ClearOverlayChildren(class UOverlay* OverlayRef);
};
