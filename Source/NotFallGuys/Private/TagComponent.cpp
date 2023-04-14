#include "TagComponent.h"

#include "LeaderboardSubsystem.h"
#include "TagPlayerState.h"

void UTagComponent::InitializeTaggedPlayers(TArray<APlayerState*> players)
{
	maxTaggedPlayers = dataAsset ? dataAsset->MaxTaggedPlayers() : 1;
	const int randomIndex = FMath::RandRange(0, players.Num()-1);
	AddTaggedPlayer(players[randomIndex]);
}

void UTagComponent::SwapTaggedPlayer(APlayerState* oldPlayer, APlayerState* newPlayer)
{
	RemoveTaggedPlayer(oldPlayer);
	AddTaggedPlayer(newPlayer);
}

TArray<APlayerState*> UTagComponent::GetTaggedPlayers()
{
	return taggedPlayers;
}

void UTagComponent::TerminateTaggedPlayers()
{
	ULeaderboardSubsystem* leaderboardSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULeaderboardSubsystem>();
	if(!leaderboardSubsystem) return;
	int taggedScore = dataAsset ? dataAsset->GetTaggedScore() : 1000.0f;
	for (APlayerState* taggedPlayer : taggedPlayers)
	{
		FLeaderboardData data = FLeaderboardData(taggedPlayer->GetPlayerName(), taggedScore);
		leaderboardSubsystem->AddLeaderboardData(data);
		ATagPlayerState* tagPlayerState = Cast<ATagPlayerState>(taggedPlayer);
		if(tagPlayerState)
		{
			tagPlayerState->MULTICAST_EndScreen(data);
		}
	}
}

void UTagComponent::AddTaggedPlayer(APlayerState* playerState)
{
	if(IsTaggedPlayersFull()) return;
	if(taggedPlayers.Contains(playerState)) return;
	taggedPlayers.Add(playerState);
	SetTaggedPlayersCount();
	OnPlayerTaggedEvent.Broadcast(playerState, true);
}

void UTagComponent::RemoveTaggedPlayer(APlayerState* playerState)
{
	if(!taggedPlayers.Contains(playerState)) return;
	taggedPlayers.Remove(playerState);
	SetTaggedPlayersCount();
	OnPlayerTaggedEvent.Broadcast(playerState, false);
}

bool UTagComponent::IsTaggedPlayersFull() const
{
	return taggedPlayersCount >= maxTaggedPlayers;
}

void UTagComponent::SetTaggedPlayersCount()
{
	taggedPlayersCount = taggedPlayers.Num();
}