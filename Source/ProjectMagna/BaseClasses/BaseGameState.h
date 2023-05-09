// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProjectMagna/ProjectMagna.h"
#include "BaseGameState.generated.h"

UCLASS()
class PROJECTMAGNA_API ABaseGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGameState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GetLeadingTeam(TArray<int32> Scores, ETeam& Team, int32& BiggestScore);

	virtual void SetTeamScore(const ETeam Team, const int32 NewScore);
	virtual int32 GetTeamScore(const ETeam Team);
	virtual void OffsetTeamScore(const ETeam Team, const int32 Offset);
	
};
