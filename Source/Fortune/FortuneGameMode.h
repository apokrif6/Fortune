#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FortuneGameMode.generated.h"

UCLASS(minimalapi)
class AFortuneGameMode : public AGameModeBase
{
	GENERATED_BODY()

	USoundBase* GameOverSound;
public:
	AFortuneGameMode();

	UFUNCTION()
	void OnPlayerKilled();

	void RestartLevel();
};



