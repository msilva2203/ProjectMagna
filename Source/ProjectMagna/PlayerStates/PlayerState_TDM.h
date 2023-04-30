// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BasePlayerState.h"
#include "PlayerState_TDM.generated.h"

UCLASS()
class PROJECTMAGNA_API APlayerState_TDM : public ABasePlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerState_TDM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
