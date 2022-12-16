#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Fortune/UI/Prompt/Prompt.h"
#include "Fortune/UI/Prompt/PromptWidget.h"
#include "GameFramework/Actor.h"
#include "PromptTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKFOnPromptTrigger);

UCLASS()
class FORTUNE_API APromptTrigger : public AActor
{
	GENERATED_BODY()

public:
	APromptTrigger();
	
	UPROPERTY(EditAnywhere, Category = BoxCollision)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintAssignable)
	FKFOnPromptTrigger OnPromptTrigger;
	
	Prompt Prompt;

protected:
	virtual void BeginPlay() override;

public:
	void ShowPrompt();

	void FreezePlayer();
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
