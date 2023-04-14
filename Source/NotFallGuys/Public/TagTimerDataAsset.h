#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TagTimerDataAsset.generated.h"

UCLASS()
class NOTFALLGUYS_API UTagTimerDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	float PlayersWaitTime() const { return playersWaitTime; }
	float StartWaitTime() const { return startWaitTime; }
	float MatchWaitTime() const { return matchWaitTime; }
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin =0.0f)) float playersWaitTime;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin =0.0f)) float startWaitTime;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin =0.0f)) float matchWaitTime;
};
