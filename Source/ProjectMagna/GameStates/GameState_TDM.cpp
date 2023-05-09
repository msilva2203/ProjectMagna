// Created and developed by Marco Silva


#include "GameState_TDM.h"

#include "Net/UnrealNetwork.h"
#include "ProjectMagna/Gamemodes/GameMode_TDM.h"
#include "ProjectMagna/PlayerControllers/PlayerController_TDM.h"
#include "ProjectMagna/Statics/MagnaStatics.h"


void AGameState_TDM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AGameState_TDM, GoalObjective);
	DOREPLIFETIME(AGameState_TDM, ScoreTeam1);
	DOREPLIFETIME(AGameState_TDM, ScoreTeam2);
	DOREPLIFETIME(AGameState_TDM, TimeRemaining);
}

// Sets default values
AGameState_TDM::AGameState_TDM() :
	GoalObjective(-1),
	ScoreTeam1(-1),
	ScoreTeam2(-1),
	TimeRemaining(-1)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

void AGameState_TDM::SetTeamScore(const ETeam Team, const int32 NewScore)
{
	switch (Team)
	{
	case ETeam::Team01:
		ScoreTeam1 = NewScore;
		if (GetNetMode() == NM_ListenServer)
		{
			OnRep_ScoreTeam1();
		}
		break;
	case ETeam::Team02:
		ScoreTeam2 = NewScore;
		if (GetNetMode() == NM_ListenServer)
		{
			OnRep_ScoreTeam2();
		}
		break;
	default:
		break;
	}
}

int32 AGameState_TDM::GetTeamScore(const ETeam Team)
{
	switch (Team)
	{
	case ETeam::Team01:
		return ScoreTeam1;
	case ETeam::Team02:
		return ScoreTeam2;
	default:
		return -1;
	}
}

void AGameState_TDM::OffsetTeamScore(const ETeam Team, const int32 Offset)
{
	int32 NewScore = GetTeamScore(Team) + Offset;
	SetTeamScore(Team, NewScore);
}

void AGameState_TDM::SetGoalObjective(const int32 NewObjective)
{
	GoalObjective = NewObjective;

	if (GetNetMode() == NM_ListenServer)
		OnRep_GoalObjective();
	
}


void AGameState_TDM::SetTimeRemaining(const int32 NewTime)
{
	TimeRemaining = NewTime;
	
	if (GetNetMode() == NM_ListenServer)
		OnRep_TimeRemaining();

	if (TimeRemaining <= 0)
	{
		Cast<AGameMode_TDM>(AuthorityGameMode)->EndGame();
	}
}

void AGameState_TDM::OffsetTimeRemaining(const int32 Offset)
{
	SetTimeRemaining(TimeRemaining + Offset);
}

void AGameState_TDM::OnRep_GoalObjective()
{
	GetPlayerController()->GetGameHUD()->SetObjectiveGoal(GoalObjective);
}

void AGameState_TDM::OnRep_ScoreTeam1()
{
	if (GetPlayerController()->GetTeam() == ETeam::Team01)
	{
		GetPlayerController()->GetGameHUD()->SetPlayerTeamScore(ScoreTeam1);
	}
	else
	{
		GetPlayerController()->GetGameHUD()->SetEnemyTeamScore(ScoreTeam1);
	}
	
}

void AGameState_TDM::OnRep_ScoreTeam2()
{
	if (GetPlayerController()->GetTeam() == ETeam::Team02)
	{
		GetPlayerController()->GetGameHUD()->SetPlayerTeamScore(ScoreTeam2);
	}
	else
	{
		GetPlayerController()->GetGameHUD()->SetEnemyTeamScore(ScoreTeam2);
	}
	
}

void AGameState_TDM::OnRep_TimeRemaining()
{
	GetPlayerController()->GetGameHUD()->SetTimeRemaining(TimeRemaining);
	
}

APlayerController_TDM* AGameState_TDM::GetPlayerController()
{
	if (PlayerController_TDM)
	{
		return PlayerController_TDM;
	}
	else
	{
		PlayerController_TDM = Cast<APlayerController_TDM>(GetWorld()->GetFirstPlayerController());
		return PlayerController_TDM;
	}
}

