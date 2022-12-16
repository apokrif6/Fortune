#include "RandomNumberWidget.h"

void URandomNumberWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GenerateRandom();

	GenerateButton->OnClicked.AddUniqueDynamic(this, &URandomNumberWidget::OnGenerateButtonClicked);
}

void URandomNumberWidget::GenerateRandom()
{
	int32 RandomNumber = FMath::RandRange(0, 100);
	
	RandomNumberLabel->SetText(FText::AsNumber(RandomNumber));
}

void URandomNumberWidget::OnGenerateButtonClicked()
{
	GenerateRandom();
}