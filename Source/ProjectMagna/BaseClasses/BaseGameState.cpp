// Created and developed by Marco Silva


#include "BaseGameState.h"


// Sets default values
ABaseGameState::ABaseGameState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABaseGameState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGameState::GetLeadingTeam(TArray<int32> Scores, ETeam& Team, int32& BiggestScore)
{
	int32 Index = 0;
	BiggestScore = Scores[Index];

	for (int i = 1; i < Scores.Num(); i++)
	{
		if (Scores[i] > BiggestScore)
		{
			Index = i;
			BiggestScore = Scores[Index];
		}
	}

	Team = static_cast<ETeam>(Index+1);
}

void ABaseGameState::SetTeamScore(const ETeam Team, const int32 NewScore)
{
}

int32 ABaseGameState::GetTeamScore(const ETeam Team)
{
	return -1;
}

void ABaseGameState::OffsetTeamScore(const ETeam Team, const int32 Offset)
{
}

