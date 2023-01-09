#include "WaterKillzone.h"

#include "Fortune/FortuneCharacter.h"
#include "Kismet/GameplayStatics.h"

AWaterKillzone::AWaterKillzone()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(FName("Box collision"));
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetupAttachment(RootComponent);
}

void AWaterKillzone::BeginPlay()
{ 
	Super::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWaterKillzone::OnStep);
}

void AWaterKillzone::OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AFortuneCharacter>(OtherActor) == nullptr)
	{
		return;
	}

	Kill();
}

void AWaterKillzone::Kill()
{
	OnPlayerKilled.Broadcast();
}
