#include "LightingNavigator.h"

#include "TexAlignTools.h"
#include "Components/BoxComponent.h"
#include "Fortune/FortuneCharacter.h"

ALightingNavigator::ALightingNavigator()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);
}

void ALightingNavigator::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALightingNavigator::OnTrigger);
}

void ALightingNavigator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightingNavigator::Appear()
{
	MarkAsTriggered();
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("T"));
	}
}

void ALightingNavigator::Disappear()
{
	
}

void ALightingNavigator::MarkAsTriggered()
{
	CanBeTriggered = false;

	GetWorldTimerManager().SetTimer(ActivityHandler, this, &ALightingNavigator::MarkAsReady, 5.f);
}

void ALightingNavigator::MarkAsReady()
{
	CanBeTriggered = true;
}


void ALightingNavigator::OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AFortuneCharacter>(OtherActor) == nullptr)
	{
		return;
	}
	
	if (CanBeTriggered)
	{
		Appear();
	}
}

