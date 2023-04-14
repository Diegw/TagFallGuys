#pragma once

#include "CoreMinimal.h"
#include "LeaderboardData.h"
#include "GameFramework/PlayerController.h"
#include "TagPlayerController.generated.h"

UCLASS()
class NOTFALLGUYS_API ATagPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent) void ShowEndScreen(FLeaderboardData data);
};