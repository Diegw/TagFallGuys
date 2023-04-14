#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TagMatchDataAsset.generated.h"

UCLASS()
class NOTFALLGUYS_API UTagMatchDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	int MaxMatchCharacters() const { return maxMatchCharacters; }
	
private:
	UPROPERTY(EditDefaultsOnly, meta = (ClampMin=2)) int maxMatchCharacters;
};