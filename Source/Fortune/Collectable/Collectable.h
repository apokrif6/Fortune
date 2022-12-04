#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Collectable.generated.h"

UINTERFACE()
class UCollectable : public UInterface
{
	GENERATED_BODY()
};

class FORTUNE_API ICollectable
{
	GENERATED_BODY()
public:
	virtual void OnCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) = 0;
};
