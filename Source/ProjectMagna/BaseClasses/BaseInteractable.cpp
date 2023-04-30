// Created and developed by Marco Silva


#include "BaseInteractable.h"

#include "ProjectMagna/Interfaces/InteractionInterface.h"
#include "BasePlayerController.h"
#include "Net/UnrealNetwork.h"
#include "ProjectMagna/Statics/MagnaStatics.h"

void ABaseInteractable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseInteractable, bActive);
}


// Sets default values
ABaseInteractable::ABaseInteractable() :
	bActive(true)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	FVector BoxExtent = FVector(50.0f, 50.0f, 50.0f);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseInteractable::OnBoxBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseInteractable::OnBoxEndOverlap);
	BoxComponent->SetBoxExtent(BoxExtent, true);

	this->bReplicates = true;
}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseInteractable::Destroyed()
{
	if (IsValid(CurrentActor))
	{
		IInteractionInterface* Interface = Cast<IInteractionInterface>(CurrentActor);
		if (Interface)
		{
			Interface->RemoveInteractable(this);
		}
	}
}


void ABaseInteractable::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor);
	if (Interface)
	{
		if (Interface->IsPlayer())
			if (Interface->IsLocalPlayer())
			{
				CurrentActor = OtherActor;
				Interface->AddInteractable(this);
			}
	}
}

void ABaseInteractable::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CurrentActor == OtherActor)
	{
		IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor);
		if (Interface)
		{
			if (Interface->IsPlayer())
				if (Interface->IsLocalPlayer())
				{
				
					Interface->RemoveInteractable(this);
				}
		}
	}
}

void ABaseInteractable::Interact(ABasePlayerController* PlayerController)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, TEAM_COLOR_NONE, TEXT("Interacted on the server!"));
}

bool ABaseInteractable::IsActive()
{
	return bActive;
}

void ABaseInteractable::SetActive(const bool bNewValue)
{
	bActive = bNewValue;

	const ENetMode CurrentNetMode = GetWorld()->GetNetMode();
	if (CurrentNetMode < NM_ListenServer || CurrentNetMode == NM_Client)
	{
		if (IsValid(CurrentActor))
		{
			IInteractionInterface* Interface = Cast<IInteractionInterface>(CurrentActor);
			if (Interface)
			{
				Interface->TestEntityInteractables();
			}
		}
	}
}

void ABaseInteractable::OnRep_Active()
{
	SetActive(bActive);
}


