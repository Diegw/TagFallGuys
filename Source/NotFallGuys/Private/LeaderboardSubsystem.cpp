#include "LeaderboardSubsystem.h"

void ULeaderboardSubsystem::Initialize(FSubsystemCollectionBase& collection)
{
	Super::Initialize(collection);
}

void ULeaderboardSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void ULeaderboardSubsystem::AddLeaderboardData(FLeaderboardData data)
{
	if(leaderboardData.Contains(data)) return;
	leaderboardData.Add(data);
	UpdateLeaderboard();
}

void ULeaderboardSubsystem::RemoveLeaderboardData(int index)
{
	if(!leaderboardData.IsValidIndex(index)) return;
	leaderboardData.RemoveAt(index);
}

void ULeaderboardSubsystem::UpdateLeaderboard()
{
	SortLeaderboardData();
	RemoveOutOfRangeData();
	PopulateLeaderboard();
}

void ULeaderboardSubsystem::SortLeaderboardData()
{
	leaderboardData.Sort([](const FLeaderboardData& thisData, const FLeaderboardData& thatData)
		{return thisData.PlayerScore < thatData.PlayerScore;});
}

void ULeaderboardSubsystem::RemoveOutOfRangeData()
{
	const int entriesToRemove = FMath::Max(leaderboardData.Num() - MAX_DATA_ENTRIES, 0);
	for (int i = entriesToRemove - 1; i >= 0; --i)
	{
		RemoveLeaderboardData(i);
	}
}

void ULeaderboardSubsystem::PopulateLeaderboard()
{
	leaderboard.Empty();
	for (int i = 0; i < leaderboardData.Num(); ++i)
	{
		leaderboard.Add(i, leaderboardData[i]);
	}
}
