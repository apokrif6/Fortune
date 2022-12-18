#pragma once

#include "CoreMinimal.h"
#include "FPrompt.h"
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
	void ShotPromptTriggered(FPrompt Prompt);

	UFUNCTION()
	void HidePromptTriggered();
	
public:
	void ShowPrompt(FPrompt Prompt);

	void HidePrompt();
};
