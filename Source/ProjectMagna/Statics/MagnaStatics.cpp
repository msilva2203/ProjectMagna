// Created and developed by Marco Silva


#include "MagnaStatics.h"

#include "Kismet/KismetSystemLibrary.h"
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
		return FText::FromString(TEXT("Default"));
	case EActionState::Sprinting:
		return FText::FromString(TEXT("Sprinting"));
	case EActionState::Aiming:
		return FText::FromString(TEXT("Aiming"));
	default:
		return FText::FromString(TEXT("Invalid"));
	}
}

FText UMagnaStatics::GetWeaponName(const uint8 WeaponID)
{
	switch (WeaponID)
	{
	case 0:
		return FText::FromString("");
	case 1:
		return FText::FromString("AK-47");
	case 2:
		return FText::FromString("92-FS");
	case 3:
		return FText::FromString("M4");
	default:
		return FText::FromString("");
	}
}


void UMagnaStatics::DrawDebugStringLines(UObject* WorldContextObject, const FVector OriginLocation, TArray<FString> DebugTextLines, FLinearColor Color)
{
	FString DebugString;
	for (int i = 0; i < DebugTextLines.Num(); i++)
	{
		DebugString += DebugTextLines[i];
		if (i != DebugTextLines.Num()-1)
		{
			DebugString += "\n";
		}
	}
	UKismetSystemLibrary::DrawDebugString(WorldContextObject, OriginLocation, DebugString, 0, Color);
}


