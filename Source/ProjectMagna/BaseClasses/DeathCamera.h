﻿// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "DeathCamera.generated.h"

UCLASS()
class PROJECTMAGNA_API ADeathCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADeathCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetActive(const bool bNewValue);

	UFUNCTION()
	void SetDeathInstigator(AActor* InDeathInstigator);

	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	AActor* DeathInstigator;

	UPROPERTY()
	bool bActive;
};
