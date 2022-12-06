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