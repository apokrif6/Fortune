#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Fortune/UI/Prompt/FPrompt.h"
#include "Fortune/UI/Prompt/PromptWidget.h"
#include "GameFramework/Actor.h"
#include "PromptTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPromptTrigger, FPrompt, Prompt);

UCLASS()
class FORTUNE_API APromptTrigger : public AActor
{
	GENERATED_BODY()

public:
	APromptTrigger();
	
	UPROPERTY(EditAnywhere, Category = BoxCollision)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintAssignable)
	FOnPromptTrigger OnPromptTrigger;
	
	FPrompt Prompt;

protected:
	virtual void BeginPlay() override;

public:
	void ShowPrompt();

	void PauseGame();
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
