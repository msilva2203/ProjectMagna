// Created and developed by Marco Silva


#include "GameState_TTDM.h"


// Sets default values
AGameState_TTDM::AGameState_TTDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameState_TTDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameState_TTDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

