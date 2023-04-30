// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BaseGameState.h"
#include "GameState_TTDM.generated.h"

UCLASS()
class PROJECTMAGNA_API AGameState_TTDM : public ABaseGameState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameState_TTDM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
