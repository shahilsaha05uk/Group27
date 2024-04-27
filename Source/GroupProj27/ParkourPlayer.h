// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ClimbInterface.h"
#include "Interfaces/ParkourPlayerInterface.h"
#include "Interfaces/PlayerInputInterface.h"
#include "ParkourPlayer.generated.h"

UCLASS()
class GROUPPROJ27_API AParkourPlayer : public ACharacter, public IPlayerInputInterface, public IParkourPlayerInterface, public IClimbInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float mDefaultWalkSpeed;
	
	
public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	class UArrowComponent* mTracerComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	class UCapsuleComponent* mLedgeColliderComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* mCameraHandlerComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	class UCameraComponent* mCameraComponent;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Movement")
	float mRunSpeed;

	AParkourPlayer();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlatformCollisionBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPlatformCollisionEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex);

	virtual void BeginPlay() override;

	// IParkourPlayerInterface interface methods
	virtual FVector GetCameraLookAt_Implementation() override;
	virtual void ReachedDestination_Implementation(int ID) override;

	virtual void Hang_Implementation(bool isLedgeDetected) override;
	virtual void StopHamg_Implementation() override;
	
	// IPlayerInputInterface interface methods
	virtual void Move_Implementation(const FInputActionValue& Value) override;
	virtual void Look_Implementation(const FInputActionValue& Value) override;
	virtual void StartRunning_Implementation(const FInputActionValue& Value) override;
	virtual void StopRunning_Implementation(const FInputActionValue& Value) override;
	virtual void StartJump_Implementation(const FInputActionValue& Value) override;
	virtual void StopJump_Implementation(const FInputActionValue& Value) override;
	virtual void Climb_Implementation(const FInputActionValue& Value) override;
	virtual void Slide_Implementation(const FInputActionValue& Value) override;


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetWalkSpeed(float Value);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetDefaultWalkSpeed() {return mDefaultWalkSpeed;}
};
