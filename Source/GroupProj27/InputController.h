#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"

/**
 * 
 */
UCLASS()
class GROUPPROJ27_API AInputController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UDA_Inputs* mInputData;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UInputMappingContext* mPlayerInputContext;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Privates")
	class AGameLevelMode* mGameMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Privates")
	APawn* mPawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Settings")
	float mMinCamPitch;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera Settings")
	float mMaxCamPitch;

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

#pragma region Player Actions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartRunning(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopRunning(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartJump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopJump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Climb(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Slide(const FInputActionValue& Value);

#pragma endregion
};
