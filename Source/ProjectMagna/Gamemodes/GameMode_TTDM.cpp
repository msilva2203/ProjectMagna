// Created and developed by Marco Silva


#include "GameMode_TTDM.h"

#include "ProjectMagna/GameStates/GameState_TTDM.h"
#include "ProjectMagna/PlayerControllers/PlayerController_TTDM.h"
#include "ProjectMagna/PlayerStates/PlayerState_TTDM.h"


// Sets default values
AGameMode_TTDM::AGameMode_TTDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->GameStateClass = AGameState_TTDM::StaticClass();
	this->PlayerStateClass = APlayerState_TTDM::StaticClass();
	this->PlayerControllerClass = APlayerController_TTDM::StaticClass();

	this->NumTeams = 3;
	this->MinPlayers = 3;
}

// Called when the game starts or when spawned
void AGameMode_TTDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameMode_TTDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

