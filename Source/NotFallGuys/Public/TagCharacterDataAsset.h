#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TagCharacterDataAsset.generated.h"

UCLASS()
class NOTFALLGUYS_API UTagCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	FName JumpInputName() { return jumpInputName; };
	FName MoveXInputName() { return moveXInputName; };
	FName MoveYInputName() { return moveYInputName; };
	FName RotateXInputName() { return rotateXInputName; };
	FName RotateYInputName() { return rotateYInputName; };
	float CameraDistance() { return cameraDistance; };
	float TurnAtSpeed() { return turnAtSpeed; };
	float LookAtSpeed() { return lookAtSpeed; };

private:
	UPROPERTY(EditDefaultsOnly) FName jumpInputName;
	UPROPERTY(EditDefaultsOnly) FName moveXInputName;
	UPROPERTY(EditDefaultsOnly) FName moveYInputName;
	UPROPERTY(EditDefaultsOnly) FName rotateXInputName;
	UPROPERTY(EditDefaultsOnly) FName rotateYInputName;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=1)) float cameraDistance;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=1)) float turnAtSpeed;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=1)) float lookAtSpeed;
};
