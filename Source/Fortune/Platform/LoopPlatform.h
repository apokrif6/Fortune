#pragma once

#include "CoreMinimal.h"
#include "Platform.h"
#include "LoopPlatform.generated.h"

UCLASS()
class FORTUNE_API ALoopPlatform : public APlatform
{
	GENERATED_BODY()
	
public:
	ALoopPlatform();

	virtual void BeginPlay() override;


protected:
	virtual void Move() override;

	virtual void CreateCurve() override;
};
