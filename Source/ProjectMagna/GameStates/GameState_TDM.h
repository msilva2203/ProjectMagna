// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BaseGameState.h"
#include "GameState_TDM.generated.h"

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
};
