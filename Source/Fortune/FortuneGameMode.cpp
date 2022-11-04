// Copyright Epic Games, Inc. All Rights Reserved.

#include "FortuneGameMode.h"
#include "FortuneCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFortuneGameMode::AFortuneGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
