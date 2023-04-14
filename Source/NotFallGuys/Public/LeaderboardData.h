#pragma once

#include "LeaderboardData.generated.h"

USTRUCT(BlueprintType)
struct FLeaderboardData
{
	GENERATED_BODY()

	FORCEINLINE FLeaderboardData();
	explicit FORCEINLINE FLeaderboardData(FString name, float score);

	bool operator==(const FLeaderboardData& newData) const;
	bool operator!=(const FLeaderboardData& newData) const;
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) FString PlayerName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly) float PlayerScore;
	bool IsDataEmpty() const { return PlayerName == FString(); }
};

FORCEINLINE FLeaderboardData::FLeaderboardData()
{
	PlayerName = FString();
	PlayerScore = 0;
}

FORCEINLINE FLeaderboardData::FLeaderboardData(FString name, float score)
{
	PlayerName = name;
	PlayerScore = score;
}

FORCEINLINE bool FLeaderboardData::operator==(const FLeaderboardData& newData) const
{
	return PlayerName == newData.PlayerName && PlayerScore == newData.PlayerScore;
}

FORCEINLINE bool FLeaderboardData::operator!=(const FLeaderboardData& newData) const
{
	return PlayerName != newData.PlayerName || PlayerScore != newData.PlayerScore;
}