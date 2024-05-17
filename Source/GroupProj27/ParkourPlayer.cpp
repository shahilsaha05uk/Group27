// Fill out your copyright notice in the Description page of Project Settings.


#include "ParkourPlayer.h"

#include "InputActionValue.h"
#include "PizzaTimeInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAssets/DA_CharacterDetails.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GroupProj27/Subsystems/CustomerSubsystem.h"

// Sets default values
AParkourPlayer::AParkourPlayer()
{
	mCameraHandlerComponent = CreateDefaultSubobject<USpringArmComponent>("Camera Handler");
	mCameraHandlerComponent->SetupAttachment(RootComponent);

	mCameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	mCameraComponent->SetupAttachment(mCameraHandlerComponent);
}

void AParkourPlayer::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AParkourPlayer::Init_Implementation()
{
	mDefaultWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	mDefaultCapsuleHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	
	const auto Instance = GetGameInstance();
	UCustomerSubsystem *CustomerSubs = Instance->GetSubsystem<UCustomerSubsystem>();

	SetCharacterMesh();
	
	if(CustomerSubs)
	{
		CustomerSubs->OnChefReviewGenerated.AddDynamic(this, &ThisClass::OnChefReviewRecieved);
	}

}

#pragma region Player Input Implementation
void AParkourPlayer::Move_Implementation(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AParkourPlayer::Look_Implementation(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AParkourPlayer::StartJump_Implementation(const FInputActionValue& Value)
{
	Jump();
}

void AParkourPlayer::StopJump_Implementation(const FInputActionValue& Value)
{
	StopJumping();
}

void AParkourPlayer::Roll_Implementation(const FInputActionValue& Value)
{

}

#pragma endregion

#pragma region UI Inputs

void AParkourPlayer::PauseGame_Implementation()
{

}

void AParkourPlayer::TogglePhone_Implementation()
{

}

void AParkourPlayer::OnChefReviewRecieved_Implementation(int avgReview)
{
	
}

void AParkourPlayer::SetCharacterMesh()
{

	if(mCharacterDetailsAsset == nullptr)
	{
		GetMesh()->SetSkeletalMeshAsset(mDefaultCharacterMesh);
	}
	else
	{
		const auto id = Cast<UPizzaTimeInstance>(GetGameInstance())->CharacterID;
		const auto mesh = mCharacterDetailsAsset->CharacterDetails.Find(id);
		if(mesh != nullptr)
		{
			GetMesh()->SetSkeletalMeshAsset(mesh->CharacterMesh);
		}
		else
		{
			GetMesh()->SetSkeletalMeshAsset(mDefaultCharacterMesh);
		}
	}
}

void AParkourPlayer::SetCapsuleHeight(float Value, bool UpdateOverlaps)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(Value, UpdateOverlaps);
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

void AParkourPlayer::ReachedDestination_Implementation(int ID)
{
	
}

void AParkourPlayer::OnOrdersRequested_Implementation()
{
	
}

UCharacterMovementComponent* AParkourPlayer::GetMovementComp_Implementation()
{
	return GetCharacterMovement();
}

ACharacter* AParkourPlayer::GetCharacter_Implementation()
{
	return this;
}