// Created and developed by Marco Silva


#include "KillVolume.h"

#include "ProjectMagna/Interfaces/CombatInterface.h"
#include "ProjectMagna/Interfaces/InteractionInterface.h"


// Sets default values
AKillVolume::AKillVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	if (BoxComponent)
	{
		SetRootComponent(BoxComponent);
		BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AKillVolume::OnBoxBeginOverlap);
		
	}
}

// Called when the game starts or when spawned
void AKillVolume::BeginPlay()
{
	Super::BeginPlay();

	// Destroys the Kill Volume if current world is not the server
	if (GetWorld()->GetNetMode() >= NM_Client)
		K2_DestroyActor();
	
}

// Called every frame
void AKillVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AKillVolume::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetWorld()->GetNetMode() < NM_Client)
	{
		ICombatInterface* Interface = Cast<ICombatInterface>(OtherActor);
		if (Interface)
		{
			FDamageData Damage;
			Damage.Damage = Interface->GetCurrentHealth();

			Interface->Damage(OtherActor, Damage);
		}
	}
}
