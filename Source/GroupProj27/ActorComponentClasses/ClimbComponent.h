// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClimbComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCLimbableLedgeFoundSignature, AActor*, Ledge);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType )
class GROUPPROJ27_API UClimbComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	AActor* mSelectedActor;
	
public:

	UPROPERTY(BlueprintReadWrite, Category = "Private")
	APawn* mPawnRef;
	UPROPERTY(BlueprintReadWrite, Category = "Private")
	class UArrowComponent* mArrow;
	UPROPERTY(BlueprintReadWrite, Category = "Private")
	class UCapsuleComponent* mLedgeCollider;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Platform")
	float mPlatformDetectionCapsuleRadius = 55.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Platform")
	float mPlatformDetectionCapsuleHeight = 42.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Ledge")
	float mLedgeDetectionCapsuleRadius = 19.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Ledge")
	float mLedgeDetectionCapsuleHeight = 42.0f;

	
	UClimbComponent();

	UFUNCTION(BlueprintCallable)
	void Init(class UArrowComponent* arrow, class UCapsuleComponent* LedgeCollider);

	// Climbing
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AttemptToHang();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Detect();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Hang();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopHang();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TraceForAValidPlatform(FVector Start, FVector End, FHitResult &hit);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool TraceForAValidLedge(FVector Start, FVector End, FHitResult &hit);
};
