#pragma once

#include "CoreMinimal.h"
#include "TagGameModeComponent.h"
#include "TagSpawnDataAsset.h"
#include "TagSpawnComponent.generated.h"

UCLASS()
class NOTFALLGUYS_API UTagSpawnComponent : public UTagGameModeComponent
{
	GENERATED_BODY()

public:	
	UTagSpawnComponent();
	void CheckToSpawnCharacter(APlayerController* playerController = nullptr) const;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditDefaultsOnly) UTagSpawnDataAsset* dataAsset;
	APawn* SpawnCharacter() const;
	TSubclassOf<APawn> GetCharacterToSpawn() const;
};
