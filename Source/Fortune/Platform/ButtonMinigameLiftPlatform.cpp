#include "ButtonMinigameLiftPlatform.h"
#include "Fortune/Interactable/ButtonsMinigame/ButtonsMinigame.h"
#include "Kismet/GameplayStatics.h"

AButtonMinigameLiftPlatform::AButtonMinigameLiftPlatform()
{
	TArray<AActor*> FoundMinigames;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AButtonsMinigame::StaticClass(), FoundMinigames);

	for (int i = 0; i < FoundMinigames.Num(); i++)
	{
		AButtonsMinigame* TmpButtonsMinigame = Cast<AButtonsMinigame>(FoundMinigames[i]);
		TmpButtonsMinigame->OnGameWon.AddDynamic(this, &AButtonMinigameLiftPlatform::GameWon);
	}
}

void AButtonMinigameLiftPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	HidePlatform();
}

void AButtonMinigameLiftPlatform::GameWon()
{
	ShowPlatform();
}

void AButtonMinigameLiftPlatform::HidePlatform()
{
	SetActorHiddenInGame(true);
}

void AButtonMinigameLiftPlatform::ShowPlatform()
{
	if (ShowPlatformParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShowPlatformParticle, GetActorLocation());
	}
	
	SetActorHiddenInGame(false);
}
