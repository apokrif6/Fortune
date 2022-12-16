#pragma once

#include "CoreMinimal.h"
#include "Prompt.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "PromptWidget.generated.h"

UCLASS()
class FORTUNE_API UPromptWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();
	
protected:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* PromptTextLabel;

	UFUNCTION()
	void PromptTriggered();

public:
	void ShowPrompt(Prompt Prompt);
};
