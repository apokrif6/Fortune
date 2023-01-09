#include "FortuneGameMode.h"
#include "FortuneCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "WaterKillzone/WaterKillzone.h"

AFortuneGameMode::AFortuneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	TArray<AActor*> FoundKillzones;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaterKillzone::StaticClass(), FoundKillzones);

	for (int i = 0; i < FoundKillzones.Num(); i++)
	{
		AWaterKillzone* TmpKillzones = Cast<AWaterKillzone>(FoundKillzones[i]);
		TmpKillzones->OnPlayerKilled.AddDynamic(this, &AFortuneGameMode::OnPlayerKilled);
	}
}
void AFortuneGameMode::OnPlayerKilled()
{
	//TODO
	//Add widget with "You died"
	RestartLevel();
}

void AFortuneGameMode::RestartLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}
