#pragma once

#include "CoreMinimal.h"
#include "TagGameModeComponent.h"
#include "TagTimerDataAsset.h"
#include "TagTimerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTagTimerDelegate);

UCLASS()
class NOTFALLGUYS_API UTagTimerComponent : public UTagGameModeComponent
{
	GENERATED_BODY()

public:
	UTagTimerComponent();
	UPROPERTY() FTagTimerDelegate OnPlayersTimerFinished;
	UPROPERTY() FTagTimerDelegate OnStartTimerFinished;
	UPROPERTY() FTagTimerDelegate OnMatchTimerFinished;
	void EnableStartTimer();
	void EnableMatchTimer();
	void SetGameStateTimers();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(VisibleAnywhere) bool doesPlayersTimerFinished;
	UPROPERTY(VisibleAnywhere) float waitPlayersTimer;
	UPROPERTY(VisibleAnywhere) bool doesStartTimerFinished;
	UPROPERTY(VisibleAnywhere) float waitStartTimer;
	UPROPERTY(VisibleAnywhere) bool doesMatchTimerFinished;
	UPROPERTY(VisibleAnywhere) float waitMatchTimer;
	UPROPERTY(EditDefaultsOnly) UTagTimerDataAsset* dataAsset;
	
	void UpdateTimer(bool& checkTimer, float& timer, FTagTimerDelegate& delegate, float deltaTime);
	void SetTimerState(bool& timerState, bool newState);
};