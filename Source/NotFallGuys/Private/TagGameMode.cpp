#include "TagGameMode.h"

#include "LeaderboardSubsystem.h"
#include "TagComponent.h"
#include "TagPlayerState.h"
#include "TagTimerComponent.h"
#include "TagSpawnComponent.h"
#include "ToggleInputInterface.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

ATagGameMode::ATagGameMode()
{
	bots = 0.0f;
	TimerComponent = CreateDefaultSubobject<UTagTimerComponent>("Timer Component");
	SpawnComponent = CreateDefaultSubobject<UTagSpawnComponent>("Spawn Component");
	TagComponent = CreateDefaultSubobject<UTagComponent>("Tag Component");
}

void ATagGameMode::SetNewTagPlayer(APlayerState* oldPlayer, APlayerState* newPlayer)
{
	TagComponent->SwapTaggedPlayer(oldPlayer, newPlayer);
}

void ATagGameMode::BeginPlay()
{
	Super::BeginPlay();
	TimerComponent->OnPlayersTimerFinished.AddDynamic(this, &ATagGameMode::OnTimerForPlayersEnded);
	TimerComponent->OnStartTimerFinished.AddDynamic(this, &ATagGameMode::OnTimerForStartEnded);
	TimerComponent->OnMatchTimerFinished.AddDynamic(this, &ATagGameMode::OnTimerForMatchEnded);
	TagComponent->OnPlayerTaggedEvent.AddDynamic(this, &ATagGameMode::OnPlayerTagged);
}

void ATagGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ATagGameMode::PostLogin(APlayerController* newPlayerController)
{
	Super::PostLogin(newPlayerController);
	SpawnComponent->CheckToSpawnCharacter(newPlayerController);
	TryToStartMatch();
}

void ATagGameMode::OnTimerForPlayersEnded()
{
	const int botsToSpawn = dataAsset ? dataAsset->MaxMatchCharacters() - NumPlayers : 0;
	for (int i = 0; i < botsToSpawn; ++i)
	{
		SpawnComponent->CheckToSpawnCharacter();
		bots++;
	}
	TryToStartMatch();
}

void ATagGameMode::TryToStartMatch()
{
	if(!ReadyToStartMatch()) return;
	StartMatch();
	TimerComponent->EnableStartTimer();
}

void ATagGameMode::StartMatch()
{
	Super::StartMatch();
	TagComponent->InitializeTaggedPlayers(GameState->PlayerArray);
	UE_LOG(LogTemp, Error, TEXT("Start Match"));
}

void ATagGameMode::OnTimerForStartEnded()
{
	SetPlayersInputEnable(true);
	TimerComponent->EnableMatchTimer();
}

void ATagGameMode::OnTimerForMatchEnded()
{
	UE_LOG(LogTemp, Error, TEXT("EndMatch"));
	SetPlayersInputEnable(false);
	TagComponent->TerminateTaggedPlayers();
	EndMatch();
}

void ATagGameMode::OnPlayerTagged(APlayerState* player, bool isTagged)
{
	ATagPlayerState* tagPlayerState = Cast<ATagPlayerState>(player);
	if(tagPlayerState)
	{
		tagPlayerState->SetIsTagged(isTagged);
	}
}

void ATagGameMode::OnMatchStateSet()
{
	Super::OnMatchStateSet();
}

bool ATagGameMode::ReadyToStartMatch_Implementation()
{
	if(HasMatchStarted()) return false;
	if(NumPlayers < 1) return false;
	const int maxCharacters = dataAsset ? dataAsset->MaxMatchCharacters() : 2;
	if(NumPlayers + bots < maxCharacters) return false;
	return true;
}

bool ATagGameMode::ReadyToEndMatch_Implementation()
{
	return false;
}

void ATagGameMode::SetPlayersInputEnable(bool enable)
{
	if(!GameState || GameState->PlayerArray.Num() <= 0) return;
	for (APlayerState* playerState : GameState->PlayerArray)
	{
		IToggleInputInterface* inputInterface = Cast<IToggleInputInterface>(playerState->GetPawn());
		if(!inputInterface) continue;
		inputInterface->SetInputState(enable);
	}
}
