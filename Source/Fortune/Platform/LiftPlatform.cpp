#include "LiftPlatform.h"

#include "Fortune/FortuneCharacter.h"


ALiftPlatform::ALiftPlatform()
{
	BasicSetup();
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box collision"));
	BoxCollision->SetCollisionProfileName(TEXT("Trigger"));
	BoxCollision->SetupAttachment(RootComponent);
}

void ALiftPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALiftPlatform::OnStep);
}


void ALiftPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALiftPlatform::OnStep(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AFortuneCharacter>(OtherActor) == nullptr)
	{
		return;
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Step!"));
	}

	Move();
}


void ALiftPlatform::Move()
{
	if (CurveFloat)
	{
		FOnTimelineFloat ProgressFunction;

		ProgressFunction.BindUFunction(this, HandleRequestFunctionName);

		Timeline.AddInterpFloat(CurveFloat, ProgressFunction);
		SetLooping(false);

		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

		Timeline.PlayFromStart();
	}
}

void ALiftPlatform::CreateCurve()
{
	CurveFloat->FloatCurve.UpdateOrAddKey(0.f, 0.f);
	CurveFloat->FloatCurve.UpdateOrAddKey(SecondsToArriveTarget, 1.f);
}
