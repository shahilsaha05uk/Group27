// Fill out your copyright notice in the Description page of Project Settings.


#include "ClimbComponent.h"

#include "Components/ArrowComponent.h"
#include "GroupProj27/HelperClasses/HelperMethods.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "GroupProj27/Interfaces/ClimbInterface.h"
#include "GroupProj27/Interfaces/LedgeInterface.h"
#include "GroupProj27/Interfaces/ParkourPlayerInterface.h"
#include "GroupProj27/Interfaces/PlatformInterface.h"
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

void UClimbComponent::AttemptToHang_Implementation()
{
}

bool UClimbComponent::Detect_Implementation()
{
	return false;
}

void UClimbComponent::Hang_Implementation()
{
	AActor* Owner = GetOwner();
	if(UKismetSystemLibrary::DoesImplementInterface(Owner, UClimbInterface::StaticClass()))
	{
		IClimbInterface::Execute_Hang(Owner);
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
