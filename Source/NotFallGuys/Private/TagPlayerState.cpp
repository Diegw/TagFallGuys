#include "TagPlayerState.h"
#include "TagCharacter.h"
#include "TagPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

ATagPlayerState::ATagPlayerState()
{
	bReplicates = true;
}

void ATagPlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ATagPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATagPlayerState, isTagged);
}

bool ATagPlayerState::GetIsTagged() const
{
	return isTagged;
}

void ATagPlayerState::SetIsTagged(bool newState)
{
	isTagged = newState;
}

void ATagPlayerState::OnRep_IsTagged()
{
	ATagCharacter* tagCharacter = GetPawn<ATagCharacter>();
	if(tagCharacter)
	{
		tagCharacter->SetNewMaterial(isTagged);
	}
}

bool ATagPlayerState::MULTICAST_EndScreen_Validate(FLeaderboardData data) { return true; }
void ATagPlayerState::MULTICAST_EndScreen_Implementation(FLeaderboardData data)
{
	ATagPlayerController* tagPlayerController = GetInstigatorController<ATagPlayerController>();
	if(tagPlayerController && tagPlayerController->IsLocalPlayerController())
	{
		tagPlayerController->ShowEndScreen(data);
	}
}

