// Created and developed by Marco Silva


#include "PlayerController_FFA.h"


// Sets default values
APlayerController_FFA::APlayerController_FFA()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Gamemode = EGamemode::Ffa;
}

// Called when the game starts or when spawned
void APlayerController_FFA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerController_FFA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

