// Created and developed by Marco Silva


#include "PlayerState_TTDM.h"


// Sets default values
APlayerState_TTDM::APlayerState_TTDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerState_TTDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerState_TTDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

