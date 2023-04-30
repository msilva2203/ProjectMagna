// Created and developed by Marco Silva


#include "GameState_FFA.h"


// Sets default values
AGameState_FFA::AGameState_FFA()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameState_FFA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameState_FFA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

