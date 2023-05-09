// Created and developed by Marco Silva


#include "GameHUD_TDM.h"

#include "ProjectMagna/Statics/MagnaStatics.h"

void UGameHUD_TDM::NativePreConstruct()
{
	Super::NativePreConstruct();

	Score_PlayerTeam->SetBackgroundColor(TEAM_COLOR_HEROES);
	Score_EnemyTeam->SetBackgroundColor(TEAM_COLOR_VILLAINS);
	Score_ObjectiveGoal->SetBackgroundColor(TEAM_COLOR_NONE);
}


void UGameHUD_TDM::NativeConstruct()
{
	Super::NativeConstruct();
	
}


void UGameHUD_TDM::SetTimeRemaining(const int32 Time)
{
	GameTimer->SetTime(Time);
}

void UGameHUD_TDM::SetPlayerTeamScore(const int32 NewScore)
{
	Score_PlayerTeam->SetScore(NewScore);
}

void UGameHUD_TDM::SetEnemyTeamScore(const int32 NewScore)
{
	Score_EnemyTeam->SetScore(NewScore);
}

void UGameHUD_TDM::SetObjectiveGoal(const int32 NewScore)
{
	Score_ObjectiveGoal->SetScore(NewScore);
}


