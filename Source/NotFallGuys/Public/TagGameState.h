#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TagGameState.generated.h"

UCLASS()
class NOTFALLGUYS_API ATagGameState : public AGameState
{
	GENERATED_BODY()

public:
	ATagGameState();
	
	UFUNCTION(BlueprintCallable) int GetStartTime();
	UFUNCTION(NetMulticast, WithValidation, Unreliable) void MULTICAST_SetStartTime(float time);
	
	UFUNCTION(BlueprintCallable) int GetMatchTime();
	UFUNCTION(NetMulticast, WithValidation, Unreliable) void MULTICAST_SetMatchTime(float time);
	
private:
	UPROPERTY(VisibleAnywhere, Category = GameState) int startTime;
	UPROPERTY(VisibleAnywhere, Category = GameState) int matchTime;
};
