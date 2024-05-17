// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnumClass.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StructClass.generated.h"


USTRUCT(BlueprintType)
struct FCharacterDetails
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int ID;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTexture2D* Image;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USkeletalMesh* CharacterMesh;	
};

USTRUCT(BlueprintType)
struct FMinMaxStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int min;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int max;

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
	TEnumAsByte<EPizzaQuality> QualityType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int DecreaseRate;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Review;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UTexture2D* Icon;
	
	FPizzaStruct(int id, int quality, int dRate, FString review): QualityType(Best), Icon(nullptr)
	{
		ID = id;
		Quality = quality;
		DecreaseRate = dRate;
		Review = review;
	}

	FPizzaStruct(): ID(0), Quality(0), QualityType(Best), DecreaseRate(0), Icon(nullptr)
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
