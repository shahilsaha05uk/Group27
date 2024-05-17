// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupProj27/HelperClasses/EnumClass.h"
#include "Shop.generated.h"

UENUM()
enum EColliderToggle
{
	CountdownCollider,
	NormalCollider,
	NoCollider,
	BothCollider
};


UCLASS()
class GROUPPROJ27_API AShop : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UStaticMeshComponent* mShopMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USphereComponent* mNormalCollider;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class USphereComponent* mCountdownCollider;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UPizzaComponent* mPizzaComp;

	AShop();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void Init();

	UFUNCTION(BlueprintCallable)
	void OnCountdownColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void OnNormalColliderOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOrderCollected(FString ID, int RemainingOrders);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnDecisionMade(EGameDecision Decision);
	UFUNCTION(BlueprintCallable)
	void OnTimerFinished();
	UFUNCTION(BlueprintCallable, BlueprintCallable)
	void MakeOrders(AActor* PlayerRef);
	UFUNCTION(BlueprintCallable)
	void ToggleCollider(EColliderToggle ColliderToToggle);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleShop(bool Activate);
	
	UFUNCTION(BlueprintCallable)
	void UpdateEntities(AActor* target);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int AverageOrderQuality = 0;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int CalculateAverage();
	
};
