// Created and developed by Marco Silva


#include "PlayerState_TDM.h"


// Sets default values
APlayerState_TDM::APlayerState_TDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerState_TDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerState_TDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

