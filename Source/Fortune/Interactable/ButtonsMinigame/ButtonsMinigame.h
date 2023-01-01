#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Fortune/Interactable/Interactable.h"
#include "ButtonsMinigame.generated.h"

UCLASS()
class FORTUNE_API AButtonsMinigame : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	AButtonsMinigame();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GreenButton;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BlackButton;
	
	virtual void Interact() override;
};
