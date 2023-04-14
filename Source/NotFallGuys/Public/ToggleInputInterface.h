#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ToggleInputInterface.generated.h"

UINTERFACE(MinimalAPI)
class UToggleInputInterface : public UInterface
{
	GENERATED_BODY()
};

class NOTFALLGUYS_API IToggleInputInterface
{
	GENERATED_BODY()

public:
	virtual void SetInputState(bool enable) { }
};
