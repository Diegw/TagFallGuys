#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TagDataAsset.generated.h"

UCLASS()
class NOTFALLGUYS_API UTagDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
 	int MaxTaggedPlayers() const { return maxTaggedPlayers; }
	float GetTaggedScore() const { return taggedScore; }
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=1)) int maxTaggedPlayers;
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=1)) float taggedScore;
};
