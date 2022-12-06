#pragma once

#include "CoreMinimal.h"
#include "Fortune/Collectable/Collectable.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Coin.generated.h"

UCLASS()
class FORTUNE_API ACoin : public AActor, public ICollectable
{
	GENERATED_BODY()

public:
	ACoin();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CoinMesh;

	UPROPERTY(VisibleAnywhere)
	URotatingMovementComponent* RotatingMovementComponent;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
