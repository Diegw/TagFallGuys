#pragma once

#include "CoreMinimal.h"
#include "TagMatchDataAsset.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/PlayerState.h"
#include "TagGameMode.generated.h"

class UTagTimerComponent;
class UTagSpawnComponent;
class UTagComponent;

UCLASS()
class NOTFALLGUYS_API ATagGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATagGameMode();
	void SetNewTagPlayer(APlayerState* oldPlayer, APlayerState* newPlayer);
	
protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* newPlayerController) override;
	virtual void StartMatch() override;
	virtual void OnMatchStateSet() override;
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Category=Timer, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UTagTimerComponent* TimerComponent;

	UPROPERTY(Category=Spawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UTagSpawnComponent* SpawnComponent;

	UPROPERTY(Category=Spawn, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UTagComponent* TagComponent;

	UPROPERTY(EditDefaultsOnly) UTagMatchDataAsset* dataAsset;
	
	int bots;
	void TryToStartMatch();
	UFUNCTION() void OnTimerForPlayersEnded();
	UFUNCTION() void OnTimerForStartEnded();
	UFUNCTION() void OnTimerForMatchEnded();
	UFUNCTION() void OnPlayerTagged(APlayerState* player, bool isTagged);
	void SetPlayersInputEnable(bool enable);
};
