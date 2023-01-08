#pragma once

#include "CoreMinimal.h"
#include "LiftPlatform.h"
#include "ButtonMinigameLiftPlatform.generated.h"

UCLASS()
class FORTUNE_API AButtonMinigameLiftPlatform : public ALiftPlatform
{
	GENERATED_BODY()

	AButtonMinigameLiftPlatform();

	void BeginPlay() override;
	
public:
	UPROPERTY(EditAnywhere, Category = ParticleEffect)
	UParticleSystem* ShowPlatformParticle;

	UFUNCTION()
	void GameWon();

	void HidePlatform();

	void ShowPlatform();
};
