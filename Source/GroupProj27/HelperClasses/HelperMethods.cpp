// Fill out your copyright notice in the Description page of Project Settings.


#include "HelperMethods.h"

FBounds UHelperMethods::GetBounds(AActor* actor)
{
	if(!actor) return FBounds();
	FVector origin, extent;
	actor->GetActorBounds(false, origin, extent, false);
	FBounds bounds;
	bounds.Origin = origin;
	bounds.Extent = extent;
	bounds.Top = origin + FVector(0,0, extent.Z);
	bounds.Bottom = origin - FVector(0,0, extent.Z);
	bounds.LeftOnX = origin - FVector(extent.X,0, 0);
	bounds.RightOnX = origin + FVector(extent.X,0, 0);
	bounds.LeftOnY = origin - FVector(0,extent.Y, 0);
	bounds.RightOnY = origin + FVector(0,extent.Y, 0);
	return bounds;
}

FPlayerBoxTracePositions UHelperMethods::GetPlayerBoxTracePositions(FVector StartPos)
{
	FPlayerBoxTracePositions pos;
	pos.Up_StartPos = FVector(StartPos.X, StartPos.Y, StartPos.Z * 2.0f);
	pos.Up_EndPos = pos.Up_StartPos + FVector::DownVector;

	pos.Down_StartPos = FVector(StartPos.X, StartPos.Y, StartPos.Z / 2.0f);
	pos.Down_EndPos = pos.Down_StartPos + FVector::DownVector;

	return pos;
}

