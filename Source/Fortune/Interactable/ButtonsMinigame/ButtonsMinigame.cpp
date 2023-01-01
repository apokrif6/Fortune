#include "ButtonsMinigame.h"

AButtonsMinigame::AButtonsMinigame()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera component"));
	CameraComponent->SetupAttachment(RootComponent);

	GreenButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Green button"));
	GreenButton->SetupAttachment(RootComponent);
	BlackButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black button"));
	BlackButton->SetupAttachment(RootComponent);
}


void AButtonsMinigame::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Game started!"));


	
}
