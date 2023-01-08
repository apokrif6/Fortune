#include "ButtonsMinigame.h"

#include "Fortune/FortuneCharacter.h"
#include "Kismet/GameplayStatics.h"

AButtonsMinigame::AButtonsMinigame()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera component"));
	CameraComponent->SetupAttachment(RootComponent);

	RedButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Red button"));
	RedButton->SetupAttachment(RootComponent);
	PurpleButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black button"));
	PurpleButton->SetupAttachment(RootComponent);
	BlueButton = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Blue button"));
	BlueButton->SetupAttachment(RootComponent);
}

void AButtonsMinigame::BeginPlay()
{
	Super::BeginPlay();
	
	RedButton->OnClicked.AddDynamic(this, &AButtonsMinigame::OnRedButtonClicked);
	PurpleButton->OnClicked.AddDynamic(this, &AButtonsMinigame::OnPurpleButtonClicked);
	BlueButton->OnClicked.AddDynamic(this, &AButtonsMinigame::OnBlueButtonClicked);
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
	PlayResultSound(RightAnswerSound);

	OnGameWon.Broadcast();
}

void AButtonsMinigame::Lose()
{
	PlayResultSound(WrongAnswerSound);
}

void AButtonsMinigame::PlayResultSound(USoundBase* SoundBase)
{
	UGameplayStatics::PlaySoundAtLocation(this, SoundBase, GetActorLocation());
}

void AButtonsMinigame::OnRedButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	CurrentAnswer.Push(1);

	CheckAnswer();
}

void AButtonsMinigame::OnPurpleButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	CurrentAnswer.Push(2);

	CheckAnswer();
}

void AButtonsMinigame::OnBlueButtonClicked(UPrimitiveComponent* PrimitiveComponent, FKey Key)
{
	CurrentAnswer.Push(3);

	CheckAnswer();
}
