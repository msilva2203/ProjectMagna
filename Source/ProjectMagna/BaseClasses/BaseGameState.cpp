// Created and developed by Marco Silva


#include "BaseGameState.h"


// Sets default values
ABaseGameState::ABaseGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

