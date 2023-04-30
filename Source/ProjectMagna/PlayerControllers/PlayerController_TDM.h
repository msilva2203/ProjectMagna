// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BasePlayerController.h"
#include "PlayerController_TDM.generated.h"

UCLASS()
class PROJECTMAGNA_API APlayerController_TDM : public ABasePlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerController_TDM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
