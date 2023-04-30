// Created and developed by Marco Silva


#include "PlayerSpawner.h"

#include "BaseCharacter.h"
#include "BasePlayerController.h"
#include "ProjectMagna/Statics/MagnaStatics.h"


// Sets default values
APlayerSpawner::APlayerSpawner() :
	CharacterClass(ABaseCharacter::StaticClass()),
	bAvailable(true),
	CycleTime(10.0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	CapsuleComponent->SetupAttachment(GetRootComponent());
	ArrowComponent->SetupAttachment(CapsuleComponent);

	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCapsuleHalfHeight(88.0);
	CapsuleComponent->SetCapsuleRadius(34.0);
	CapsuleComponent->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
	CapsuleComponent->ShapeColor = UMagnaStatics::GetTeamColor(SpawnerTeam);
	ArrowComponent->SetHiddenInGame(true);
	ArrowComponent->SetVisibility(true);
	ArrowComponent->SetRelativeLocation(FVector(0.0, 0.0, 0.0));
	ArrowComponent->SetArrowColor(UMagnaStatics::GetTeamColor(SpawnerTeam));
	
}

// Called when the game starts or when spawned
void APlayerSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ABaseCharacter* APlayerSpawner::SpawnPlayer(ABasePlayerController* Player)
{
	const ETeam Team = Player->GetTeam();
	const FTransform Transform = ArrowComponent->GetComponentTransform();
	
	UWorld* World = GetWorld();
	ABaseCharacter* NewCharacter = World->SpawnActorDeferred<ABaseCharacter>(CharacterClass, Transform);
	//Setup Player Character here...
	NewCharacter->MaxHealth = 100.0f;
	NewCharacter->CurrentHealth = 100.0f;
	NewCharacter->CharacterPlayerController = Player;
	
	NewCharacter->FinishSpawning(Transform);
	NewCharacter->SetOwner(Player);
	Player->SetControlRotation(ArrowComponent->GetComponentRotation());
	Player->Possess(NewCharacter);
	Player->SetPlayerGameState(EPlayerGameState::Playing);
	NewCharacter->SetupCharacter();
	SetAvailable(false);
	
	return NewCharacter;
}

bool APlayerSpawner::IsAvailable() const
{
	return bAvailable;
}

ETeam APlayerSpawner::GetTeam() const
{
	return SpawnerTeam;
}

void APlayerSpawner::SetAvailable(const bool bNewValue)
{
	bAvailable = bNewValue;

	if (bAvailable)
	{
		if (SpawnerCycleTimer.IsValid())
		{
			GetWorldTimerManager().ClearTimer(SpawnerCycleTimer);
		}
	}
	else
	{
		GetWorldTimerManager().SetTimer(SpawnerCycleTimer, this, &APlayerSpawner::OnSpawnerCycleEnd, CycleTime, false);
	}
}

void APlayerSpawner::OnSpawnerCycleEnd()
{
	SetAvailable(true);
	
}

