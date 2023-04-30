// Created and developed by Marco Silva


#include "PlayerController_TDM.h"


// Sets default values
APlayerController_TDM::APlayerController_TDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Gamemode = EGamemode::Tdm;
}

// Called when the game starts or when spawned
void APlayerController_TDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerController_TDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

