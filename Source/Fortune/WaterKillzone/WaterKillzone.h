#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMeshActor.h"
#include "WaterKillzone.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FKOnPlayerKilled);

UCLASS()
class FORTUNE_API AWaterKillzone : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AWaterKillzone();      

	UPROPERTY(BlueprintAssignable)
	FKOnPlayerKilled OnPlayerKilled;
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	
	virtual void BeginPlay() override;
	
	void Kill();

	UFUNCTION()
	void OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
