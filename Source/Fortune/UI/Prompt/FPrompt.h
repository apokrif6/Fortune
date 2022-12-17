#pragma once

#include "FPrompt.generated.h"

USTRUCT(BlueprintType)
struct FPrompt
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString PromptText;

	FPrompt()
	{
		PromptText = FString("Test prompt");
	}

	FPrompt(FString IPromptText)
	{
		PromptText = IPromptText;
	}
};
