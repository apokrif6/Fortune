#include "Coin.h"

ACoin::ACoin()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CoinMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Coin mesh"));
	CoinMesh->SetStaticMesh(CoinMeshAsset.Object);
	CoinMesh->SetCollisionProfileName(TEXT("Trigger"));
	CoinMesh->SetupAttachment(RootComponent);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating movement"));
}

void ACoin::BeginPlay()
{
	Super::BeginPlay();

	CoinMesh->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnCollect);
}

void ACoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACoin::OnCollect(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Collected!"));
		Destroy();
	}
}


