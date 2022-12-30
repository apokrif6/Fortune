#include "InteractableCube.h"

AInteractableCube::AInteractableCube()
{
}

void AInteractableCube::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableCube::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Interacted!"));
}
