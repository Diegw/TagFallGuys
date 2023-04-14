#include "TagGameModeComponent.h"
#include "TagGameState.h"

ATagGameState* UTagGameModeComponent::TagGameState()
{
	if(!tagGameState)
	{
		tagGameState = Cast<ATagGameState>(GetWorld()->GetGameState());
	}
	return tagGameState;
}