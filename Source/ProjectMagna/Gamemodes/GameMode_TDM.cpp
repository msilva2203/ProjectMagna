// Created and developed by Marco Silva


#include "GameMode_TDM.h"

#include "ProjectMagna/GameStates/GameState_TDM.h"
#include "ProjectMagna/PlayerControllers/PlayerController_TDM.h"
#include "ProjectMagna/PlayerStates/PlayerState_TDM.h"


// Sets default values
AGameMode_TDM::AGameMode_TDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->GameStateClass = AGameState_TDM::StaticClass();
	this->PlayerStateClass = APlayerState_TDM::StaticClass();
	this->PlayerControllerClass = APlayerController_TDM::StaticClass();

	this->NumTeams = 2;
	this->MinPlayers = 3;
}

// Called when the game starts or when spawned
void AGameMode_TDM::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameMode_TDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGameMode_TDM::StartGame()
{
	Super::StartGame();

	GameState_TDM = Cast<AGameState_TDM>(GameState);
	
	GameState_TDM->SetTimeRemaining(20*60);
	GameState_TDM->SetGoalObjective(50);
	GameState_TDM->SetTeamScore(ETeam::Team01, 0);
	GameState_TDM->SetTeamScore(ETeam::Team02, 0);
	
}

void AGameMode_TDM::EndGame()
{
	Super::EndGame();
}

void AGameMode_TDM::GameTimeCallback()
{
	Super::GameTimeCallback();

	GameState_TDM->OffsetTimeRemaining(-1);
}

// Debug Commands

void AGameMode_TDM::game_set_time(int32 value)
{
	Super::game_set_time(value);
	
	GameState_TDM->SetTimeRemaining(value);
}


void AGameMode_TDM::game_set_goal(int32 value)
{
	Super::game_set_goal(value);
	
	GameState_TDM->SetGoalObjective(value);
}

void AGameMode_TDM::game_set_teamscore(int32 team, int32 value)
{
	if (team <= NumTeams)
	{
		value = FMath::Clamp<int32>(value, 0, 999999);
		team = FMath::Clamp<int32>(team, 0, NumTeams);
		ETeam Team = (ETeam)team;

		GameState_TDM->SetTeamScore(Team, value);
	}
}

