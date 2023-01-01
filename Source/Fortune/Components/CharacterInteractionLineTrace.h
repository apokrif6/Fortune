#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CharacterInteractionLineTrace.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORTUNE_API UCharacterInteractionLineTrace : public USceneComponent
{
	GENERATED_BODY()

public:	
	UCharacterInteractionLineTrace();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Trace")
	float TraceDistance = 500.0f;
	
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InteractWithObject();
};
