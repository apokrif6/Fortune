#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "LightingNavigator.generated.h"

UCLASS()
class FORTUNE_API ALightingNavigator : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ALightingNavigator();

	UPROPERTY(EditAnywhere, Category = TriggerCollider)
	UBoxComponent* Trigger;

	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ActivityHandler;
	
	bool CanBeTriggered = true;

	void MarkAsTriggered();

	void MarkAsReady();
	
	void Appear();

	void Disappear();
};
