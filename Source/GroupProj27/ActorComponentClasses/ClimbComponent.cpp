// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"

#include "Components/ArrowComponent.h"
#include "GroupProj27/HelperClasses/HelperMethods.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "GroupProj27/Interfaces/LedgeInterface.h"
#include "GroupProj27/Interfaces/ParkourPlayerInterface.h"
#include "GroupProj27/Interfaces/PlatformInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{

}

void UClimbComponent::Init(UArrowComponent* arrow)
{
	mArrow = arrow;
	mPawnRef = Cast<APawn>(GetOwner());
}

void UClimbComponent::OnPlatformDetected_Implementation(AActor* Platform)
{
	if(!Platform) return;
	mCurrentPlatform = Platform;
}

void UClimbComponent::OnPlatformLost_Implementation()
{
	mCurrentPlatform = nullptr;
}

bool UClimbComponent::isValidPlatform(AActor*& platformRef)
{
	FVector StartPos = mArrow->GetComponentLocation();
	FVector EndPos = StartPos + GetOwner()->GetActorForwardVector() * mSightDistance;
	
	return TraceThePlatform(StartPos, EndPos, platformRef);
}

void UClimbComponent::StartCheckingClimbPossibility_Implementation()
{
	AActor* platformRef;
	if(!isValidPlatform(platformRef)) return;	// if there is a valid platform nearby

	if(UKismetSystemLibrary::DoesImplementInterface(platformRef, UPlatformInterface::StaticClass()))
	{
		IPlatformInterface::Execute_UpdateBuildingLedgeAvailability(platformRef, GetOwner());
		/*
		Dehighlight();
		mHitActors = IPlatformInterface::Execute_GetLedges(platformRef);
		Highlight(mHitActors);

		FVector Origin = GetOwner()->GetActorLocation();
		float distanceToTheLedge;
		AActor* nearestLegde = UGameplayStatics::FindNearestActor(Origin, mHitActors, distanceToTheLedge);

		if(nearestLegde) OnValidLedgeFound.Broadcast(nearestLegde);
	*/
	}
}

void UClimbComponent::StopCheckingClimbPossibility_Implementation()
{
	EdgeTestTimeHandle.Invalidate();
	mHitActors.Empty();
}

float UClimbComponent::GetClimbableDistanceFromPlayer(FVector hitLocation, AActor* BuildingRef)
{
	const FBounds bounds = UHelperMethods::GetBounds(BuildingRef);
	const FVector distanceBetweenPlayerAndBuildingTop = {hitLocation.X, hitLocation.Y, bounds.Top.Z};
			
	return FVector::Distance(hitLocation, distanceBetweenPlayerAndBuildingTop);
}

#pragma region Sighting
void UClimbComponent::StartSighting_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(EdgeTestTimeHandle, this, &UClimbComponent::Sighting, 0.001f, true);
}

void UClimbComponent::Sighting()
{
	FVector CamLoc = IParkourPlayerInterface::Execute_GetCameraLookAt(mPawnRef);
	FVector Start = mArrow->GetComponentLocation();
	FVector End = Start + CamLoc * mSightDistance;

	FHitResult hit;
	if(TraceTheFocussedLedge(Start, End, hit))
	{
		AActor* tmpActor = hit.GetActor();
		
		if(!mHitActors.Contains(tmpActor)) return;
		
		FVector hitLoc = hit.Location;
		Deselect();

		if(UKismetSystemLibrary::DoesImplementInterface(tmpActor, ULedgeInterface::StaticClass()))
		{
			AActor* buildingRef = ILedgeInterface::Execute_GetBuildingRef(tmpActor);
			float distance = GetClimbableDistanceFromPlayer(hitLoc, buildingRef);
			Select(tmpActor, distance < mClimbableDistance);
		}
	}
	else
	{
		Deselect();
	}
}

void UClimbComponent::StopSighting_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(EdgeTestTimeHandle);
	EdgeTestTimeHandle.Invalidate();
	Deselect();
}

#pragma endregion

// Selecting the focussed ledge
void UClimbComponent::Select_Implementation(AActor* actorRef, bool isStandable)
{
	if(actorRef == nullptr) return;

	if(UKismetSystemLibrary::DoesImplementInterface(actorRef, ULedgeInterface::StaticClass()))
	{
		ILedgeInterface::Execute_Select(actorRef, isStandable);
	}
	mSelectedActor = actorRef;
}

void UClimbComponent::Deselect_Implementation()
{
	if(mSelectedActor == nullptr) return;

	if(mSelectedActor == nullptr) return;

	if(UKismetSystemLibrary::DoesImplementInterface(mSelectedActor, ULedgeInterface::StaticClass()))
	{
		ILedgeInterface::Execute_Deselect(mSelectedActor);
	}
	mSelectedActor = nullptr;
}

// Highlighting
void UClimbComponent::Highlight_Implementation(const TArray<AActor*>& overlappedActors)
{
	for (auto a : overlappedActors)
	{
		if(UKismetSystemLibrary::DoesImplementInterface(a, ULedgeInterface::StaticClass()))
		{
			ILedgeInterface::Execute_Highlight(a);
		}

		if(!mHitActors.Contains(a)) mHitActors.Add(a);
	}
}

void UClimbComponent::Dehighlight_Implementation()
{
	for (auto a : mHitActors)
	{
		AActor* tmpActor = a;
		if(UKismetSystemLibrary::DoesImplementInterface(tmpActor, ULedgeInterface::StaticClass()))
		{
			ILedgeInterface::Execute_Dehighlight(tmpActor);
		}
	}
	mHitActors.Empty();
}


// Traces
bool UClimbComponent::TraceTheNearbyLedges(TArray<AActor*>& overlappedActors)	// Done Initially
{
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), mArrow->GetComponentLocation(), mSphereTraceRadius, 12, FLinearColor::Blue, 3.0f, 2.0f);
	return UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetOwner()->GetActorLocation(),
		mSphereTraceRadius, mObjectType, mSphereTraceToFilterClass, mActorsToIgnore, overlappedActors);
}

bool UClimbComponent::TraceTheFocussedLedge(FVector Start, FVector End, FHitResult& hit)	// Done during the tick
{
	return UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, mSightRadius, mSightTraceChannel,
									 false, mActorsToIgnore, EDrawDebugTrace::ForOneFrame, hit, true);
}

bool UClimbComponent::TraceThePlatform(FVector Start, FVector End, AActor*& platformRef)
{
	FHitResult hit;
	bool isSuccess = UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, mPlatformTraceChannel,
									  false, mActorsToIgnore, EDrawDebugTrace::ForDuration, hit, true);
	platformRef = hit.GetActor();
	return isSuccess;
}
