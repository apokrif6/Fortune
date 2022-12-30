#include "CharacterInteractionLineTrace.h"
#include "DrawDebugHelpers.h"
#include "Fortune/Interactable/Interactable.h"

UCharacterInteractionLineTrace::UCharacterInteractionLineTrace()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterInteractionLineTrace::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterInteractionLineTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector EndLocation = GetForwardVector() * TraceDistance + StartLocation;

	FHitResult Hit;
	FCollisionQueryParams TraceParams;
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, TraceParams);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Orange, false, 0.1f);

	if (bHit)
	{
		IInteractable* Interactable = Cast<IInteractable>(Hit.GetActor());
		if (Interactable)
		{
			Interactable->Interact();
		}
	}
}

