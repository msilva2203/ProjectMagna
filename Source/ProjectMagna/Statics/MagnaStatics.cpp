// Created and developed by Marco Silva


#include "MagnaStatics.h"

#include "ProjectMagna/BaseClasses/BaseGameMode.h"


FColor UMagnaStatics::GetEntityColor(const ETeam PlayerTeam, const ETeam EntityTeam, const EGamemode Gamemode)
{
	if (PlayerTeam == EntityTeam)
		return TEAM_COLOR_HEROES;
	
	if (Gamemode != EGamemode::Ttdm)
		return TEAM_COLOR_VILLAINS;
	
	return TEAM_COLOR_THIRD_PARTY;
}

FColor UMagnaStatics::GetTeamColor(const ETeam Team)
{
	switch (Team)
	{
	case ETeam::None:
		return TEAM_COLOR_NONE;
	case ETeam::Team01:
		return TEAM_COLOR_HEROES;
	case ETeam::Team02:
		return TEAM_COLOR_VILLAINS;
	case ETeam::Team03:
		return TEAM_COLOR_THIRD_PARTY;
	default:
		return TEAM_COLOR_VILLAINS;
	}
}

FText UMagnaStatics::GetActionStateName(const EActionState ActionState)
{
	switch (ActionState)
	{
	case EActionState::None:
		return FText::FromString(TEXT("No State"));
	case EActionState::Default:
		return FText::FromString(TEXT("Default State"));
	case EActionState::Sprinting:
		return FText::FromString(TEXT("Sprinting State"));
	case EActionState::Aiming:
		return FText::FromString(TEXT("Aiming State"));
	default:
		return FText::FromString(TEXT("Invalid State"));
	}
}

