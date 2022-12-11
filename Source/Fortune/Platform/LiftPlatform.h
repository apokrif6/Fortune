#pragma once

#include "CoreMinimal.h"
#include "Platform.h"
#include "Components/BoxComponent.h"
#include "LiftPlatform.generated.h"

UCLASS()
class FORTUNE_API ALiftPlatform : public APlatform
{
	GENERATED_BODY()
	
public:
	ALiftPlatform();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = BoxCollision)
	UBoxComponent* BoxCollision;
	
	UFUNCTION()
	virtual void OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void Move() override;

	virtual void CreateCurve() override;
};
