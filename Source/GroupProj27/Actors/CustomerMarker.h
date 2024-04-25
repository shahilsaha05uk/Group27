// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupProj27/HelperClasses/StructClass.h"
#include "CustomerMarker.generated.h"

UCLASS()
class GROUPPROJ27_API ACustomerMarker : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FCustomerStruct mCustomerDetails;

};
