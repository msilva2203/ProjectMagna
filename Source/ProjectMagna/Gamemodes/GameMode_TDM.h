// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BaseGameMode.h"
#include "GameMode_TDM.generated.h"

// Forward Declarations
class AGameState_TDM;

UCLASS()
class PROJECTMAGNA_API AGameMode_TDM : public ABaseGameMode
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameMode_TDM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartGame() override;
	virtual void EndGame() override;
	virtual void GameTimeCallback() override;

public:
	UPROPERTY()
	AGameState_TDM* GameState_TDM;

public:
	virtual void game_set_time(int32 value) override;
	virtual void game_set_goal(int32 value) override;
	virtual void game_set_teamscore(int32 team, int32 value) override;
	
};
