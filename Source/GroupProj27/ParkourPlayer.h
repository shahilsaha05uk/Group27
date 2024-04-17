// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInputInterface.h"
#include "GameFramework/Character.h"
#include "ParkourPlayer.generated.h"

UCLASS()
class GROUPPROJ27_API AParkourPlayer : public ACharacter, public IPlayerInputInterface
{
	GENERATED_BODY()

public:
	AParkourPlayer();

	virtual void Move_Implementation(const FInputActionValue& Value) override;
	virtual void Look_Implementation(const FInputActionValue& Value) override;
	virtual void StartRunning_Implementation(const FInputActionValue& Value) override;
	virtual void StopRunning_Implementation(const FInputActionValue& Value) override;
	virtual void StartJump_Implementation(const FInputActionValue& Value) override;
	virtual void StopJump_Implementation(const FInputActionValue& Value) override;
	virtual void Climb_Implementation(const FInputActionValue& Value) override;
	virtual void Slide_Implementation(const FInputActionValue& Value) override;
};
