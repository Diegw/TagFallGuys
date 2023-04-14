#pragma once

#include "CoreMinimal.h"
#include "LeaderboardData.h"
#include "GameFramework/PlayerState.h"
#include "TagPlayerState.generated.h"

UCLASS()
class NOTFALLGUYS_API ATagPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATagPlayerState();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetIsTagged(bool newState);
	bool GetIsTagged() const;
	UFUNCTION() void OnRep_IsTagged();
	UFUNCTION(NetMulticast, WithValidation, Unreliable) void MULTICAST_EndScreen(FLeaderboardData data);
	
private:
	UPROPERTY(VisibleAnywhere, Replicatedusing=OnRep_IsTagged) bool isTagged;
};
