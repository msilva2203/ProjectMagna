// Created and developed by Marco Silva


#include "GameMode_FFA.h"

#include "ProjectMagna/GameStates/GameState_FFA.h"
#include "ProjectMagna/PlayerControllers/PlayerController_FFA.h"
#include "ProjectMagna/PlayerStates/PlayerState_FFA.h"


// Sets default values
AGameMode_FFA::AGameMode_FFA()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->GameStateClass = AGameState_FFA::StaticClass();
	this->PlayerStateClass = APlayerState_FFA::StaticClass();
	this->PlayerControllerClass = APlayerController_FFA::StaticClass();

	this->NumTeams = 8;
	this->MinPlayers = 8;
	
}

// Called when the game starts or when spawned
void AGameMode_FFA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameMode_FFA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

