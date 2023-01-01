#include "PromptWidget.h"

#include "Fortune/FortuneCharacter.h"
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
		TmpTrigger->OnPromptShowTrigger.AddDynamic(this, &UPromptWidget::ShotPromptTriggered);
	}

	AFortuneCharacter* FortuneCharacter = Cast<AFortuneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (FortuneCharacter)
	{
		FortuneCharacter->OnPromptHideTrigger.AddDynamic(this, &UPromptWidget::HidePromptTriggered);
	}
	
	return true;
}

void UPromptWidget::ShowPrompt(FPrompt Prompt)
{
	SetVisibility(ESlateVisibility::Visible);

	PromptTextLabel->SetText(FText::FromString(Prompt.PromptText));

}

void UPromptWidget::ShotPromptTriggered(FPrompt Prompt)
{
	ShowPrompt(Prompt);
}

void UPromptWidget::HidePrompt()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPromptWidget::HidePromptTriggered()
{
	HidePrompt();
}
