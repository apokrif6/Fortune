#pragma once

#include "CoreMinimal.h"
#include "Fortune/Interactable/Interactable.h"
#include "InteractableCube.generated.h"

UCLASS()
class FORTUNE_API AInteractableCube : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	AInteractableCube();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact() override;
};
