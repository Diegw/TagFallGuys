#pragma once

#include "CoreMinimal.h"
#include "TagDataAsset.h"
#include "TagGameModeComponent.h"
#include "GameFramework/PlayerState.h"
#include "TagComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTagPlayerDelegate, APlayerState*, player, bool, isTagged);

UCLASS()
class NOTFALLGUYS_API UTagComponent : public UTagGameModeComponent
{
	GENERATED_BODY()

public:
	FTagPlayerDelegate OnPlayerTaggedEvent;
	void InitializeTaggedPlayers(TArray<APlayerState*> players);
	void SwapTaggedPlayer(APlayerState* oldPlayer, APlayerState* newPlayer);
	TArray<APlayerState*> GetTaggedPlayers();
	void TerminateTaggedPlayers();

private:
	UPROPERTY(EditDefaultsOnly) UTagDataAsset* dataAsset;
	UPROPERTY(VisibleAnywhere) int maxTaggedPlayers;
	UPROPERTY(VisibleAnywhere) int taggedPlayersCount;
	UPROPERTY(VisibleAnywhere) TArray<APlayerState*> taggedPlayers;
	
	void AddTaggedPlayer(APlayerState* playerState);
	void RemoveTaggedPlayer(APlayerState* playerState);
	bool IsTaggedPlayersFull() const;
	void SetTaggedPlayersCount();
};
