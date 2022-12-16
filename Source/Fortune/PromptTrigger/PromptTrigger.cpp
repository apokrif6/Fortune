#include "PromptTrigger.h"
#include "Fortune/FortuneCharacter.h"
#include "Kismet/GameplayStatics.h"

APromptTrigger::APromptTrigger()
{
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	BoxCollision->SetCollisionProfileName(TEXT("Trigger"));
	BoxCollision->SetupAttachment(RootComponent);
}

void APromptTrigger::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APromptTrigger::OnStep);
}

void APromptTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APromptTrigger::OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AFortuneCharacter>(OtherActor) == nullptr)
	{
		return;
	}
	
	ShowPrompt();
}

void APromptTrigger::ShowPrompt()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Triggered!"));
	}

	OnPromptTrigger.Broadcast();
}
