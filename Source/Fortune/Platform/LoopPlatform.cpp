#include "LoopPlatform.h"

ALoopPlatform::ALoopPlatform()
{
	BasicSetup();
}

void ALoopPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	Move();
}


void ALoopPlatform::CreateCurve()
{
	CurveFloat->FloatCurve.UpdateOrAddKey(0.f, 0.f);
	CurveFloat->FloatCurve.UpdateOrAddKey(SecondsToArriveTarget, 1.f);
	CurveFloat->FloatCurve.UpdateOrAddKey(SecondsToArriveTarget * 2, 0.f);
}


void ALoopPlatform::Move()
{
	if (CurveFloat)
	{
		FOnTimelineFloat ProgressFunction;

		ProgressFunction.BindUFunction(this, HandleRequestFunctionName);

		Timeline.AddInterpFloat(CurveFloat, ProgressFunction);
		SetLooping(true);

		GlobalStartLocation = GetActorLocation();
		GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

		Timeline.PlayFromStart();
	}
}