// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "ArenaCamera.generated.h"

UCLASS()
class PROJECTMAGNA_API AArenaCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArenaCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SpectateCamera();

	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Arena Camera");
	int32 CameraIndex;
	
};
