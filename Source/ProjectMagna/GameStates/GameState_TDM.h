// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BaseGameState.h"
#include "GameState_TDM.generated.h"

// Forward Declarations
class APlayerController_TDM;

UCLASS()
class PROJECTMAGNA_API AGameState_TDM : public ABaseGameState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameState_TDM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetTeamScore(const ETeam Team, const int32 NewScore) override;
	virtual int32 GetTeamScore(const ETeam Team) override;
	virtual void OffsetTeamScore(const ETeam Team, const int32 Offset) override;

	void SetGoalObjective(const int32 NewObjective);
	void SetTimeRemaining(const int32 NewTime);
	void OffsetTimeRemaining(const int32 Offset);

public:
	UFUNCTION()
	void OnRep_GoalObjective();
	
	UFUNCTION()
	void OnRep_ScoreTeam1();

	UFUNCTION()
	void OnRep_ScoreTeam2();

	UFUNCTION()
	void OnRep_TimeRemaining();
	
	UFUNCTION()
	APlayerController_TDM* GetPlayerController();

public:
	UPROPERTY()
	APlayerController_TDM* PlayerController_TDM;
	
	UPROPERTY(ReplicatedUsing = OnRep_GoalObjective)
	int32 GoalObjective;
	
	UPROPERTY(ReplicatedUsing = OnRep_ScoreTeam1)
	int32 ScoreTeam1;

	UPROPERTY(ReplicatedUsing = OnRep_ScoreTeam2)
	int32 ScoreTeam2;

	UPROPERTY(ReplicatedUsing = OnRep_TimeRemaining)
	int32 TimeRemaining;
	
};
