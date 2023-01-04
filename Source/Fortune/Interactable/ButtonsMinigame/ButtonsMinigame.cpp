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

void AButtonsMinigame::BeginPlay()
{
	Super::BeginPlay();
	
	GreenButton->OnClicked.AddDynamic(this, &AButtonsMinigame::OnGreenButtonClicked);
	BlackButton->OnClicked.AddDynamic(this, &AButtonsMinigame::OnBlackButtonClicked);
}

void AButtonsMinigame::Interact()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	StartGame(PlayerController);
}

void AButtonsMinigame::StartGame(APlayerController* PlayerController)
{
	PlayerController->SetViewTargetWithBlend(CameraComponent->GetAttachmentRootActor(), CameraBlendTime);

	IgnoreMovementInput(PlayerController, true);
}

void AButtonsMinigame::EndGame()
{
	CurrentAnswer.Empty();
	
	AFortuneCharacter* FortuneCharacter = Cast<AFortuneCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FortuneCharacter->ChangeCameraToMain();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	IgnoreMovementInput(PlayerController, false);
}

void AButtonsMinigame::IgnoreMovementInput(APlayerController* PlayerController, bool bCanMove)
{
	PlayerController->bEnableClickEvents = bCanMove;
	PlayerController->SetIgnoreLookInput(bCanMove);
	PlayerController->SetIgnoreMoveInput(bCanMove);
	PlayerController->SetShowMouseCursor(bCanMove);
}

void AButtonsMinigame::CheckAnswer()
{
	if (CurrentAnswer.Num() != RightAnswer.Num())
		return;
	
	if (CurrentAnswer == RightAnswer)
	{
		Win();
	} else
	{
		Lose();
	}
	
	EndGame();
}

void AButtonsMinigame::Win()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "You win!");
	
	UGameplayStatics::PlaySoundAtLocation(this, RightAnswerSound, GetActorLocation());
}

void AButtonsMinigame::Lose()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "You lose!");

	UGameplayStatics::PlaySoundAtLocation(this, WrongAnswerSound, GetActorLocation());
}


void AButtonsMinigame::OnGreenButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	CurrentAnswer.Push(1);

	CheckAnswer();
}

void AButtonsMinigame::OnBlackButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	CurrentAnswer.Push(2);

	CheckAnswer();
}

