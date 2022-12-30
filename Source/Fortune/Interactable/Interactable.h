#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


class FORTUNE_API IInteractable
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void Interact() = 0;
};
