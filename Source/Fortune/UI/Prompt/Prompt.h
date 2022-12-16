#pragma once

struct Prompt
{
	FString PromptText;

	Prompt()
	{
		PromptText = FString("Test prompt");
	}

	Prompt(FString IPromptText)
	{
		PromptText = IPromptText;
	}
};
