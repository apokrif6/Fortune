#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RandomNumberWidget.generated.h"

UCLASS()
class FORTUNE_API URandomNumberWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RandomNumberLabel;

	UPROPERTY(Meta = (BindWidget))
	UButton* GenerateButton;

	UFUNCTION()
	void OnGenerateButtonClicked();

	void GenerateRandom();

	void NativeConstruct() override;
};
