// Created and developed by Marco Silva


#include "PlayerState_FFA.h"


// Sets default values
APlayerState_FFA::APlayerState_FFA()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerState_FFA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerState_FFA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

