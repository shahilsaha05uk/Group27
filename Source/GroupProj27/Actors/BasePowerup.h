// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePowerup.generated.h"

UCLASS()
class GROUPPROJ27_API ABasePowerup : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USphereComponent* mCollider;
	
	UPROPERTY(EditDefaultsOnly)
	int ID;

	ABasePowerup();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivatePowerup();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeactivatePowerup();
};
