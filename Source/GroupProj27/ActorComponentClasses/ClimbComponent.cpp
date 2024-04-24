// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GroupProj27/HelperClasses/HelperMethods.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "GroupProj27/Interfaces/ClimbInterface.h"
#include "GroupProj27/Interfaces/LedgeInterface.h"
#include "GroupProj27/Interfaces/ParkourPlayerInterface.h"
#include "GroupProj27/Interfaces/PlatformInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"



// Sets default values for this component's properties
UClimbComponent::UClimbComponent()
{

}

void UClimbComponent::Init(UArrowComponent* arrow, UCapsuleComponent* LedgeCollider)
{
	mLedgeCollider = LedgeCollider;
	mArrow = arrow;
	mPawnRef = Cast<APawn>(GetOwner());
}

FVector2f UClimbComponent::GetForwardOffset()
{
	const auto impactPoint = mPlatformHit.ImpactPoint;
	const auto forwardOffset = (GetOwner()->GetActorForwardVector() * mCharForwardOffset) + impactPoint;

	return FVector2f(forwardOffset.X, forwardOffset.Y);
}

void UClimbComponent::LerpLocation_Implementation(float locAlpha)
{
	const auto currentLoc = GetOwner()->GetActorLocation();
	const auto forwardOffset = GetForwardOffset();
	const auto tmpLoc = FVector(forwardOffset.X, forwardOffset.Y, currentLoc.Z);
	const auto lerpVec = UKismetMathLibrary::VLerp(currentLoc, tmpLoc, locAlpha);
	
	GetOwner()->SetActorLocation(lerpVec);
}

void UClimbComponent::LerpRotation_Implementation(float rotAlpha)
{
	const auto normal = mPlatformHit.ImpactNormal;
	const FRotator currentRot = GetOwner()->GetActorRotation();
	const FRotator newRot = {currentRot.Roll, currentRot.Pitch, normal.Z + 180.0f};
	const auto lerpRot = UKismetMathLibrary::RLerp(currentRot, newRot, rotAlpha, true);
	GetOwner()->SetActorRotation(lerpRot);
}

void UClimbComponent::AttemptToHang_Implementation()
{
}

void UClimbComponent::StopAttemptToHang_Implementation()
{
	StopDetect();
}

void UClimbComponent::Detect_Implementation()
{
	// Detect for a platform
	const auto start = mLedgeCollider->GetComponentLocation();
	const auto end = mLedgeCollider->GetUpVector() * 5.0f;

	// Valid Platform
	bIsValidPlatform = TraceForAValidPlatform(start, end, mPlatformHit);

	// Valid Ledge
	bIsValidLedge = TraceForAValidLedge(start, start, mLedgeHit);

	bDetectSuccess = (bIsValidPlatform && bIsValidLedge);

	if(bDetectSuccess)
	{
		StopAttemptToHang();
		StopDetect();
		Hang();
	}
}

void UClimbComponent::StopDetect_Implementation()
{
	mDetectTimeHandler.Invalidate();
	GetWorld()->GetTimerManager().ClearTimer(mDetectTimeHandler);
}

void UClimbComponent::Hang_Implementation()
{
	AActor* Owner = GetOwner();
	if(UKismetSystemLibrary::DoesImplementInterface(Owner, UClimbInterface::StaticClass()))
	{
		IClimbInterface::Execute_Hang(Owner, bDetectSuccess);
	}
}

void UClimbComponent::StopHang_Implementation()
{
	AActor* Owner = GetOwner();
	if(UKismetSystemLibrary::DoesImplementInterface(Owner, UClimbInterface::StaticClass()))
	{
		IClimbInterface::Execute_StopHamg(Owner);
	}
}

bool UClimbComponent::TraceForAValidPlatform_Implementation(FVector Start, FVector End, FHitResult &hit)
{
	return false;
}

bool UClimbComponent::TraceForAValidLedge_Implementation(FVector Start, FVector End, FHitResult& hit)
{
	return false;
}
