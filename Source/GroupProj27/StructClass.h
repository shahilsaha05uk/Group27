// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructClass.generated.h"


USTRUCT(BlueprintType)
struct FBounds
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Origin;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Extent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Top;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Bottom;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LeftOnX;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector RightOnX;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector LeftOnY;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector RightOnY;
};




UCLASS()
class GROUPPROJ27_API UStructClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
