// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AParkourPlayer::AParkourPlayer()
{
	mTracerComponent = CreateDefaultSubobject<UArrowComponent>("Tracer");
	mTracerComponent->SetupAttachment(GetMesh());

	mLedgeColliderComponent = CreateDefaultSubobject<UCapsuleComponent>("LedgeCollider");
	mLedgeColliderComponent->SetupAttachment(RootComponent);

	mCameraHandlerComponent = CreateDefaultSubobject<USpringArmComponent>("Camera Handler");
	mCameraHandlerComponent->SetupAttachment(RootComponent);

	mCameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	mCameraComponent->SetupAttachment(mCameraHandlerComponent);
}


void AParkourPlayer::BeginPlay()
{
	// Do the bindings
	mLedgeColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &AParkourPlayer::OnPlatformCollisionBegin);
	mLedgeColliderComponent->OnComponentEndOverlap.AddDynamic(this, &AParkourPlayer::OnPlatformCollisionEnd);
	
	mDefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	Super::BeginPlay();
}

void AParkourPlayer::OnPlatformCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                             UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AParkourPlayer::OnPlatformCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
}

#pragma region Player Input Implementation
void AParkourPlayer::Move_Implementation(const FInputActionValue& Value)
{

}

void AParkourPlayer::Look_Implementation(const FInputActionValue& Value)
{
	
}

void AParkourPlayer::StartRunning_Implementation(const FInputActionValue& Value)
{

}

void AParkourPlayer::StopRunning_Implementation(const FInputActionValue& Value)
{

}

void AParkourPlayer::StartJump_Implementation(const FInputActionValue& Value)
{

}

void AParkourPlayer::StopJump_Implementation(const FInputActionValue& Value)
{

}

void AParkourPlayer::Climb_Implementation(const FInputActionValue& Value)
{

}

void AParkourPlayer::Slide_Implementation(const FInputActionValue& Value)
{

}


#pragma endregion

void AParkourPlayer::SetWalkSpeed_Implementation(float Value)
{
	GetCharacterMovement()->MaxWalkSpeed = Value;
}

FVector AParkourPlayer::GetCameraLookAt_Implementation()
{
	return mCameraComponent->GetForwardVector();
}

void AParkourPlayer::Hang_Implementation(bool isLedgeDetected)
{
	
}

void AParkourPlayer::StopHamg_Implementation()
{
	
}
