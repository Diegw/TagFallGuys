#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TagSpawnDataAsset.generated.h"

UCLASS()
class NOTFALLGUYS_API UTagSpawnDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	TSubclassOf<APawn> TagCharacterClass() { return tagCharacterClass; }
	
private:
	UPROPERTY(EditDefaultsOnly) TSubclassOf<APawn> tagCharacterClass;
};
