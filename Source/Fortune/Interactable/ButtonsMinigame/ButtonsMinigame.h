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

	UPROPERTY(VisibleAnywhere, Category="CameraComponent")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category="CameraComponent")
	float CameraBlendTime = 1.f;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GreenButton;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BlackButton;
	
	virtual void Interact() override;

private:
	void StartGame(APlayerController* PlayerController);

	void EndGame(APlayerController* PlayerController);

	void IgnoreMovementInput(APlayerController* PlayerController, bool bCanMove);
};
