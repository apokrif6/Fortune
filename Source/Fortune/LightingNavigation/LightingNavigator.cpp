#include "LightingNavigator.h"

#include "TexAlignTools.h"
#include "Components/BoxComponent.h"
#include "Fortune/FortuneCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ALightingNavigator::ALightingNavigator()
{
	SetMobility(EComponentMobility::Movable);

	Trigger = CreateDefaultSubobject<UBoxComponent>(FName("Box collision"));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("/Game/StarterContent/Particles/P_Sparks.P_Sparks"));
	LightingParticle = Particle.Object;
}

void ALightingNavigator::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALightingNavigator::OnTrigger);

	StartLocation = GetActorLocation();
	
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void ALightingNavigator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALightingNavigator::Appear()
{
	MarkAsTriggered();
	
	UParticleSystemComponent* Test = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LightingParticle, StartLocation);

	Test->MoveComponent();
	
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

