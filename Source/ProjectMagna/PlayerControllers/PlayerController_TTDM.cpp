// Created and developed by Marco Silva


#include "PlayerController_TTDM.h"


// Sets default values
APlayerController_TTDM::APlayerController_TTDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Gamemode = EGamemode::Ttdm;
}

// Called when the game starts or when spawned
void APlayerController_TTDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerController_TTDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

