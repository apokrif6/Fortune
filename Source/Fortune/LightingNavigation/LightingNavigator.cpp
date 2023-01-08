#include "LightingNavigator.h"

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Fortune/FortuneCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

ALightingNavigator::ALightingNavigator()
{
	SetMobility(EComponentMobility::Movable);

	Trigger = CreateDefaultSubobject<UBoxComponent>(FName("Box collision"));
	Trigger->SetCollisionProfileName(TEXT("Trigger"));
	Trigger->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("/Game/FXVarietyPack/Particles/P_ky_ThunderBallHit.P_ky_ThunderBallHit"));
	LightingParticle = Particle.Object;

	PrimaryActorTick.bCanEverTick = true;
}

void ALightingNavigator::BeginPlay()
{
	Super::BeginPlay();

	MovingCurve = NewObject<UCurveFloat>();
	MovingCurve->FloatCurve.UpdateOrAddKey(0.f, 0.f);
	MovingCurve->FloatCurve.UpdateOrAddKey(SecondsToArriveTarget, 1.f);
	
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALightingNavigator::OnTrigger);

	GlobalStartLocation = GetTransform().TransformPosition(StartLocation);
	
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void ALightingNavigator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void ALightingNavigator::Appear()
{
	MarkAsTriggered();
	
	LightingParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LightingParticle, GlobalStartLocation);

	MoveEffect();
}

void ALightingNavigator::Disappear()
{
	LightingParticleSystemComponent->DestroyComponent();
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

void ALightingNavigator::MoveEffect()
{
	if (MovingCurve)
	{
		FOnTimelineFloat ProgressFunction;
		FOnTimelineEvent OnProgressFunctionFinish;
		
		ProgressFunction.BindUFunction(this, HandleRequestFunctionName);
		OnProgressFunctionFinish.BindUFunction(this, ProgressFinishFunctionName);
		
		Timeline.AddInterpFloat(MovingCurve, ProgressFunction);
		
		Timeline.PlayFromStart();

		Timeline.SetTimelineFinishedFunc(OnProgressFunctionFinish);
	}
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

void ALightingNavigator::OnTimelineFinish()
{
	Disappear();
}

void ALightingNavigator::HandleMovingProgress(float Value)
{
	const FVector LocationToMove = FMath::Lerp(GlobalStartLocation, GlobalTargetLocation, Value);

	LightingParticleSystemComponent->SetWorldLocation(LocationToMove);
}
