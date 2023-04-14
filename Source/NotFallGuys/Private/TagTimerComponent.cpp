#include "TagTimerComponent.h"
#include "TagGameState.h"

UTagTimerComponent::UTagTimerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	doesPlayersTimerFinished = true;
	waitPlayersTimer = 0.0f;
	
	doesStartTimerFinished = true;
	waitStartTimer = 0.0f;

	doesMatchTimerFinished = true;
	waitMatchTimer = 0.0f;

	SetIsReplicatedByDefault(true);
}

void UTagTimerComponent::BeginPlay()
{
	Super::BeginPlay();
	SetTimerState(doesPlayersTimerFinished, false);
	waitPlayersTimer = dataAsset ? dataAsset->PlayersWaitTime() : 0.0f;
	waitStartTimer = dataAsset ? dataAsset->StartWaitTime() : 0.0f;
	waitMatchTimer = dataAsset ? dataAsset->MatchWaitTime() : 0.0f;
	SetComponentTickEnabled(true);
}

void UTagTimerComponent::EnableStartTimer()
{
	SetTimerState(doesStartTimerFinished, false);
}

void UTagTimerComponent::EnableMatchTimer()
{
	SetTimerState(doesMatchTimerFinished, false);
}

void UTagTimerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTimer(doesPlayersTimerFinished, waitPlayersTimer, OnPlayersTimerFinished, DeltaTime);
	UpdateTimer(doesStartTimerFinished, waitStartTimer, OnStartTimerFinished, DeltaTime);
	UpdateTimer(doesMatchTimerFinished, waitMatchTimer, OnMatchTimerFinished, DeltaTime);
	
	SetGameStateTimers();
}

void UTagTimerComponent::UpdateTimer(bool& checkTimer, float& timer, FTagTimerDelegate& delegate, float deltaTime)
{
	if(checkTimer) return;
	if(timer > 0.0f)
	{
		timer -= deltaTime;
		if(timer < 0.0f) timer = 0.0f;
		return;
	}
	SetTimerState(checkTimer, true);
	delegate.Broadcast();
}

void UTagTimerComponent::SetGameStateTimers()
{
	TagGameState()->MULTICAST_SetStartTime(waitStartTimer);
	TagGameState()->MULTICAST_SetMatchTime(waitMatchTimer);
}

void UTagTimerComponent::SetTimerState(bool& timerState, bool newState)
{
	timerState = newState;
}
