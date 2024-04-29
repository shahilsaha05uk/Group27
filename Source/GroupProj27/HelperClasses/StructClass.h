// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructClass.generated.h"


USTRUCT(BlueprintType)
struct FState
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite)
	int CurrentBalance;
	UPROPERTY(BlueprintReadWrite)
	int CurrentWeek;
	UPROPERTY(BlueprintReadWrite)
	int CurrentDay;
};


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

USTRUCT(BlueprintType)
struct FPlayerBoxTracePositions
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Up_StartPos;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Up_EndPos;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Down_StartPos;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Down_EndPos;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector Full_EndPos;
};

USTRUCT(BlueprintType)
struct FPizzaStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Quality;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int DecreaseRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Review;

	FPizzaStruct(int id, int quality, int dRate, FString review)
	{
		ID = id;
		Quality = quality;
		DecreaseRate = dRate;
		Review = review;
	}

	FPizzaStruct(): ID(0), Quality(0), DecreaseRate(0)
	{
	}
};

USTRUCT(BlueprintType)
struct FCustomerStruct
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int id;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector CustomerLocation;
};

UCLASS()
class GROUPPROJ27_API UStructClass : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
};
