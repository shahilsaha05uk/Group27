// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"

#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UBaseWidget::SetOverlayAlignment(UOverlaySlot* OverlayWidgetRef, EHorizontalAlignment hAlignment,
	EVerticalAlignment vAlignment)
{
	OverlayWidgetRef->SetHorizontalAlignment(hAlignment);
	OverlayWidgetRef->SetVerticalAlignment(vAlignment);
}

void UBaseWidget::ClearOverlayChildren(UOverlay* OverlayRef)
{
	if(OverlayRef->HasAnyChildren())
	{
		auto children = OverlayRef->GetAllChildren();
		for (auto c : children)
		{
			c->RemoveFromParent();
		}
	}
}
