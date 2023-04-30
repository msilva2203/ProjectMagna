// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/ProjectMagna.h"
#include "UObject/Object.h"
#include "MagnaStatics.generated.h"


#define TEAM_COLOR_NONE				FColor::FromHex(TEXT("010101FF"))
#define TEAM_COLOR_HEROES			FColor::FromHex(TEXT("4CC711FF"))
#define TEAM_COLOR_VILLAINS			FColor::FromHex(TEXT("B30D09FF"))
#define TEAM_COLOR_THIRD_PARTY		FColor::Orange


/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UMagnaStatics : public UObject
{
	GENERATED_BODY()

public:
	static FColor GetEntityColor(const ETeam PlayerTeam, const ETeam EntityTeam, const EGamemode Gamemode);
	static FColor GetTeamColor(const ETeam Team);
	static FText GetActionStateName(const EActionState ActionState);
	
};
