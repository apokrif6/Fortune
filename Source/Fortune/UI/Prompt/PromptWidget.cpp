#include "PromptWidget.h"

#include "Fortune/PromptTrigger/PromptTrigger.h"
#include "Kismet/GameplayStatics.h"

bool UPromptWidget::Initialize()
{
	Super::Initialize();

	SetVisibility(ESlateVisibility::Hidden);

	TArray<AActor*> FoundTriggers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APromptTrigger::StaticClass(), FoundTriggers);

	for (int i = 0; i < FoundTriggers.Num(); i++)
	{
		APromptTrigger* TmpTrigger = Cast<APromptTrigger>(FoundTriggers[i]);
		TmpTrigger->OnPromptTrigger.AddDynamic(this, &UPromptWidget::PromptTriggered);
	}
	
	return true;
}

void UPromptWidget::ShowPrompt(FPrompt Prompt)
{
	SetVisibility(ESlateVisibility::Visible);

	PromptTextLabel->SetText(FText::FromString(Prompt.PromptText));

}

void UPromptWidget::PromptTriggered(FPrompt Prompt)
{
	ShowPrompt(Prompt);
}
