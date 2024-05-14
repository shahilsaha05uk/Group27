#include "InputController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "DataAssets/DA_Inputs.h"
#include "Interfaces/PlayerInputInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void AInputController::BeginPlay()
{
	Super::BeginPlay();
	PlayerCameraManager->ViewPitchMin = mMinCamPitch;
	PlayerCameraManager->ViewPitchMax = mMaxCamPitch;
}

void AInputController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {

		// Move
		EnhancedInputComponent->BindAction(mInputData->IA_Move, ETriggerEvent::Triggered, this, &AInputController::Move);

		// Look
		EnhancedInputComponent->BindAction(mInputData->IA_Look, ETriggerEvent::Triggered, this, &AInputController::Look);

		// Run
		EnhancedInputComponent->BindAction(mInputData->IA_Run, ETriggerEvent::Started, this, &AInputController::StartRunning);
		EnhancedInputComponent->BindAction(mInputData->IA_Run, ETriggerEvent::Completed, this, &AInputController::StopRunning);

		// Jump
		EnhancedInputComponent->BindAction(mInputData->IA_Jump, ETriggerEvent::Started, this, &AInputController::StartJump);
		EnhancedInputComponent->BindAction(mInputData->IA_Jump, ETriggerEvent::Completed, this, &AInputController::StopJump);

		// Climb
		EnhancedInputComponent->BindAction(mInputData->IA_Climb, ETriggerEvent::Triggered, this, &AInputController::Climb);

		// Slide
		EnhancedInputComponent->BindAction(mInputData->IA_Slide, ETriggerEvent::Triggered, this, &AInputController::Slide);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(mPlayerInputContext, 0);
	}
}

void AInputController::Look_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Look(pawn, Value);
	}
}

void AInputController::Move_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Move(pawn, Value);
	}
}

void AInputController::StartRunning_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_StartRunning(pawn, Value);
	}
}

void AInputController::StopRunning_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_StopRunning(pawn, Value);
	}
}

void AInputController::StartJump_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_StartJump(pawn, Value);
	}
}

void AInputController::StopJump_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_StopJump(pawn, Value);
	}
}

void AInputController::Climb_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Climb(pawn, Value);
	}
}

void AInputController::Slide_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Slide(pawn, Value);
	}
}