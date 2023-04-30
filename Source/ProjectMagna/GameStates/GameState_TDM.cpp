// Created and developed by Marco Silva


#include "GameState_TDM.h"


// Sets default values
AGameState_TDM::AGameState_TDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameState_TDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameState_TDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

