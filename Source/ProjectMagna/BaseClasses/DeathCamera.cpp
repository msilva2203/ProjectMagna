// Created and developed by Marco Silva


#include "DeathCamera.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADeathCamera::ADeathCamera() :
	bActive(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
}

// Called when the game starts or when spawned
void ADeathCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bActive)
	{
		if (IsValid(DeathInstigator))
		{
			FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), DeathInstigator->GetActorLocation());
			CameraComponent->SetWorldRotation(NewRotation);
		}
	}
}

void ADeathCamera::SetActive(const bool bNewValue)
{
	bActive = bNewValue;
}

void ADeathCamera::SetDeathInstigator(AActor* InDeathInstigator)
{
	DeathInstigator = InDeathInstigator;
}


