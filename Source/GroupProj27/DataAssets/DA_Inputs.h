#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "DA_Inputs.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GROUPPROJ27_API UDA_Inputs : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Inputs")
	UInputAction* IA_Move;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Inputs")
	UInputAction* IA_Look;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Inputs")
	UInputAction* IA_Jump;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI Inputs")
	UInputAction* IA_Roll;

};
