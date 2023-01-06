#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Particles/ParticleSpriteEmitter.h"
#include "LightingNavigator.generated.h"

UCLASS()
class FORTUNE_API ALightingNavigator : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ALightingNavigator();

	UPROPERTY(EditAnywhere, Category = TriggerCollider)
	UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, Category = ParticleEffect)
	UParticleSystem* LightingParticle;

	UPROPERTY(EditAnywhere)
	FTimeline Timeline;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	UCurveFloat* MovingCurve;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float SecondsToArriveTarget = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget), Category = "Effect Locations")
	FVector StartLocation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (MakeEditWidget), Category = "Effect Locations")
	FVector TargetLocation;
	
	UFUNCTION()
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTimelineFinish();
	
	UFUNCTION()
	void HandleMovingProgress(float Value);
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UParticleSystemComponent* LightingParticleSystemComponent;

	FName HandleRequestFunctionName = "HandleMovingProgress";

	FName ProgressFinishFunctionName = "OnTimelineFinish";
	
	FTimerHandle ActivityHandler;

	FVector GlobalStartLocation;
	
	FVector GlobalTargetLocation;
	
	bool CanBeTriggered = true;

	void Appear();

	void Disappear();
	
	void MarkAsTriggered();

	void MarkAsReady();
	
	void MoveEffect();
};
