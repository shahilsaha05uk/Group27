#include "InputController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
#include "DataAssets/DA_Inputs.h"
#include "DataAssets/DA_UIInputs.h"
#include "Interfaces/PlayerInputInterface.h"
#include "Interfaces/PlayerUIInputInterface.h"
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
		
		// Jump
		EnhancedInputComponent->BindAction(mInputData->IA_Jump, ETriggerEvent::Started, this, &AInputController::StartJump);
		EnhancedInputComponent->BindAction(mInputData->IA_Jump, ETriggerEvent::Completed, this, &AInputController::StopJump);

		// Roll
		EnhancedInputComponent->BindAction(mInputData->IA_Roll, ETriggerEvent::Started, this, &AInputController::Roll);

		// UI Inputs

		// Pause
		EnhancedInputComponent->BindAction(mUIInputData->IA_Pause, ETriggerEvent::Completed, this, &AInputController::PauseGame);
		
		// Toggle Phone
		EnhancedInputComponent->BindAction(mUIInputData->IA_OpenPhone, ETriggerEvent::Completed, this, &AInputController::TogglePhone);
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(mPlayerInputContext, 0);
	}
}

#pragma region UI Actions
void AInputController::PauseGame_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerUIInputInterface::StaticClass()))
	{
		IPlayerUIInputInterface::Execute_PauseGame(pawn);
	}
}

void AInputController::TogglePhone_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerUIInputInterface::StaticClass()))
	{
		IPlayerUIInputInterface::Execute_TogglePhone(pawn);
	}
}
#pragma endregion

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

void AInputController::Roll_Implementation(const FInputActionValue& Value)
{
	APawn* pawn = GetPawn();

	if(UKismetSystemLibrary::DoesImplementInterface(pawn, UPlayerInputInterface::StaticClass()))
	{
		IPlayerInputInterface::Execute_Roll(pawn, Value);
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