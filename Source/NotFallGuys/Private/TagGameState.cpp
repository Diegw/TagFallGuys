#include "TagGameState.h"

ATagGameState::ATagGameState()
{
	bReplicates = true;
}

int ATagGameState::GetStartTime()
{
	return startTime;
}

bool ATagGameState::MULTICAST_SetStartTime_Validate(float time) { return true; }
void ATagGameState::MULTICAST_SetStartTime_Implementation(float time)
{
	startTime = FMath::CeilToInt(time);
}

int ATagGameState::GetMatchTime()
{
	return matchTime;
}

bool ATagGameState::MULTICAST_SetMatchTime_Validate(float time) { return true; }
void ATagGameState::MULTICAST_SetMatchTime_Implementation(float time)
{
	matchTime = FMath::CeilToInt(time);
}
