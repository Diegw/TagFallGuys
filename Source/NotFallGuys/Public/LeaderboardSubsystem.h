#pragma once

#include "CoreMinimal.h"
#include "LeaderboardData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LeaderboardSubsystem.generated.h"

UCLASS()
class NOTFALLGUYS_API ULeaderboardSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void AddLeaderboardData(FLeaderboardData data);
	
private:
	const int MAX_DATA_ENTRIES = 10;
	TArray<FLeaderboardData> leaderboardData;
	TMap<int, FLeaderboardData> leaderboard;
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void Deinitialize() override;
	void UpdateLeaderboard();
	void SortLeaderboardData();
	void RemoveLeaderboardData(int index);
	void PopulateLeaderboard();
	void RemoveOutOfRangeData();
};
