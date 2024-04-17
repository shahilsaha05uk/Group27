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
	FTimerHandle EdgeTestTimeHandle;

	UPROPERTY()
	AActor* mSelectedActor;
	
	UFUNCTION()
	bool TraceTheNearbyLedges(TArray<AActor*>& overlappedActors);
	UFUNCTION()
	bool TraceTheFocussedLedge(FVector Start, FVector End, FHitResult& hit);
	UFUNCTION()
	bool TraceThePlatform(FVector Start, FVector End, AActor*& platformRef);

	UFUNCTION()
	void Sighting();


public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCLimbableLedgeFoundSignature OnValidLedgeFound; 
	// Multi Trace Members
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Multi Trace")
	TArray<AActor*> mHitActors;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Multi Trace")
	TArray<AActor*> mActorsToIgnore;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Multi Trace")
	float mSphereTraceRadius = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Multi Trace")
	TArray<TEnumAsByte<EObjectTypeQuery>> mObjectType;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Multi Trace")
	TSubclassOf<AActor> mSphereTraceToFilterClass;

	// Single Trace Members
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sight Trace")
	float mTraceDistance = 10000.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sight Trace")
	float mClimbableDistance = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sight Trace")
	float mSightDistance = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sight Trace")
	float mSightRadius =10.0f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Sight Trace")
	TEnumAsByte<ETraceTypeQuery> mSightTraceChannel;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Platform Trace")
	TEnumAsByte<ETraceTypeQuery> mPlatformTraceChannel;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Platform Trace")
	float mBuildingDistance = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Private")
	APawn* mPawnRef;
	UPROPERTY(BlueprintReadWrite, Category = "Private")
	class UArrowComponent* mArrow;

	// News
	UPROPERTY(BlueprintReadWrite, Category = "Private")
	AActor* mCurrentPlatform;
	
	UClimbComponent();

	UFUNCTION(BlueprintCallable)
	void Init(class UArrowComponent* arrow);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlatformDetected(AActor* Platform);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlatformLost();

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartCheckingClimbPossibility();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopCheckingClimbPossibility();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartSighting();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopSighting();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Highlight(const TArray<AActor*>& overlappedActors);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Dehighlight();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Select(AActor* actorRef, bool isStandable);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Deselect();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool isValidPlatform(AActor*& platformRef);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetLedge() {return mSelectedActor;}
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetClimbableDistanceFromPlayer(FVector hitLocation, AActor* BuildingRef);
};
