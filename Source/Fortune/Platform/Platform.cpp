#include "Platform.h"

APlatform::APlatform()
{
	BasicSetup();

	CurveFloat = CreateDefaultSubobject<UCurveFloat>(FName("Looping curve"));
}

void APlatform::BeginPlay()
{
	Super::BeginPlay();

	CreateCurve();
}

void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void APlatform::HandleMovingProgress(float Value)
{
	const FVector LocationToMove = FMath::Lerp(GlobalStartLocation, GlobalTargetLocation, Value);
	SetActorLocation(LocationToMove);
}

void APlatform::SetLooping(bool ShouldLoop = false)
{
	Timeline.SetLooping(ShouldLoop);

}

void APlatform::BasicSetup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetMobility(EComponentMobility::Movable);
}

void APlatform::Move()
{
}

void APlatform::CreateCurve()
{
}
