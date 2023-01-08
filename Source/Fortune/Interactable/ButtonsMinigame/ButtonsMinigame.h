#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Fortune/Interactable/Interactable.h"
#include "ButtonsMinigame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKOnGameWon);

UCLASS()
class FORTUNE_API AButtonsMinigame : public AStaticMeshActor, public IInteractable
{
	GENERATED_BODY()

public:
	AButtonsMinigame();

	UPROPERTY(BlueprintAssignable)
	FKOnGameWon OnGameWon;
	
	UPROPERTY(VisibleAnywhere, Category="CameraComponent")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category="CameraComponent")
	float CameraBlendTime = 1.f;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RedButton;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PurpleButton;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BlueButton;

	UPROPERTY(EditAnywhere, Category="ResultSound")
	USoundBase* RightAnswerSound;
	
	UPROPERTY(EditAnywhere, Category="ResultSound")
	USoundBase* WrongAnswerSound;
	
	
	virtual void Interact() override;

private:
	void BeginPlay() override;
	
	void StartGame(APlayerController* PlayerController);

	void EndGame();

	void IgnoreMovementInput(APlayerController* PlayerController, bool bCanMove);

	void CheckAnswer();

	void Win();

	void Lose();

	void PlayResultSound(USoundBase* SoundBase);
	
	UFUNCTION()
	virtual void OnRedButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key);

	UFUNCTION()
	virtual void OnPurpleButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key);

	UFUNCTION()
	virtual void OnBlueButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key);
	
	TArray<int> CurrentAnswer;
	
	TArray<int> RightAnswer = TArray<int> {2, 1, 3};
};
