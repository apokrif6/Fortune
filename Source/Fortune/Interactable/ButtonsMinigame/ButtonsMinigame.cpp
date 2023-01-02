#include "ButtonsMinigame.h"

#include "Fortune/FortuneCharacter.h"
#include "Kismet/GameplayStatics.h"

AButtonsMinigame::AButtonsMinigame()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera component"));
	CameraComponent->SetupAttachment(RootComponent);

	GreenButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Green button"));
	GreenButton->SetupAttachment(RootComponent);
	BlackButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black button"));
	BlackButton->SetupAttachment(RootComponent);
}


void AButtonsMinigame::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Game started!"));

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	StartGame(PlayerController);
}

void AButtonsMinigame::StartGame(APlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(CameraComponent->GetAttachmentRootActor(), CameraBlendTime);

	IgnoreMovementInput(PlayerController, true);
}

void AButtonsMinigame::EndGame(APlayerController* PlayerController)
{
	AFortuneCharacter* FortuneCharacter = Cast<AFortuneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FortuneCharacter->ChangeCameraToMain();

	IgnoreMovementInput(PlayerController, false);
}

void AButtonsMinigame::IgnoreMovementInput(APlayerController* PlayerController, bool bCanMove)
{
	PlayerController->bEnableClickEvents = bCanMove;
	PlayerController->SetIgnoreLookInput(bCanMove);
	PlayerController->SetIgnoreMoveInput(bCanMove);
	PlayerController->SetShowMouseCursor(bCanMove);
}
