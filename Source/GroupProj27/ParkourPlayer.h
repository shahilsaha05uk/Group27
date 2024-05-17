// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/ParkourPlayerInterface.h"
#include "Interfaces/PlayerInputInterface.h"
#include "Interfaces/PlayerUIInputInterface.h"
#include "ParkourPlayer.generated.h"

UCLASS()
class GROUPPROJ27_API AParkourPlayer : public ACharacter, public IPlayerInputInterface, public IParkourPlayerInterface, public IPlayerUIInputInterface
{
	GENERATED_BODY()

private:
	UPROPERTY()
	float mDefaultWalkSpeed;
public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	class USpringArmComponent* mCameraHandlerComponent;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Components")
	class UCameraComponent* mCameraComponent;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private")
	class USkeletalMesh* mDefaultCharacterMesh;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private")
	class UDA_CharacterDetails* mCharacterDetailsAsset;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Animation")
	float mRollAnimSequenceLength;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Movement")
	float mAirControl;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Movement")
	float mDefaultCapsuleHeight;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Movement")
	float mTargetCapsuleHeightWhenRolling;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Private | Movement")
	float mRunSpeed;

	AParkourPlayer();

	virtual void BeginPlay() override;

	// IParkourPlayerInterface interface methods
	virtual FVector GetCameraLookAt_Implementation() override;
	virtual void ReachedDestination_Implementation(int ID) override;
	virtual void OnOrdersRequested_Implementation() override;
	virtual UCharacterMovementComponent* GetMovementComp_Implementation() override;
	virtual ACharacter* GetCharacter_Implementation() override;

	// IPlayerInputInterface interface methods
	virtual void Move_Implementation(const FInputActionValue& Value) override;
	virtual void Look_Implementation(const FInputActionValue& Value) override;
	virtual void StartJump_Implementation(const FInputActionValue& Value) override;
	virtual void StopJump_Implementation(const FInputActionValue& Value) override;
	virtual void Roll_Implementation(const FInputActionValue& Value) override;

	// Player UI Input Interface methods
	virtual void PauseGame_Implementation() override;
	virtual void TogglePhone_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Init();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnChefReviewRecieved(int avgReview);

	
	UFUNCTION(BlueprintCallable)
	void SetCharacterMesh();
	
	UFUNCTION(BlueprintCallable)
	void SetCapsuleHeight(float Value, bool UpdateOverlaps);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetWalkSpeed(float Value);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetDefaultWalkSpeed() {return mDefaultWalkSpeed;}
};
