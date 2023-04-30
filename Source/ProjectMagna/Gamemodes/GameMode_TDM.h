// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BaseGameMode.h"
#include "GameMode_TDM.generated.h"

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
};
