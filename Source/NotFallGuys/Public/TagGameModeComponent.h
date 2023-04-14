#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TagGameModeComponent.generated.h"

class ATagGameState;

UCLASS()
class NOTFALLGUYS_API UTagGameModeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	ATagGameState* tagGameState;
	ATagGameState* TagGameState();
};
