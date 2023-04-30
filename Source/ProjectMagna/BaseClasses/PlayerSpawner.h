// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "ProjectMagna/ProjectMagna.h"
#include "PlayerSpawner.generated.h"


// Forward Declarations
class ABasePlayerController;


UCLASS()
class PROJECTMAGNA_API APlayerSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	// Methods
	//

	bool IsAvailable() const;
	ETeam GetTeam() const;

	UFUNCTION()
	ABaseCharacter* SpawnPlayer(ABasePlayerController* Player);

	UFUNCTION()
	void SetAvailable(const bool bNewValue);

	UFUNCTION()
	void OnSpawnerCycleEnd();

		//...

	//
	// Properties
	//

	UPROPERTY()
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
	UArrowComponent* ArrowComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Spawner")
	TSubclassOf<ABaseCharacter> CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Player Spawner")
	ETeam SpawnerTeam;

	UPROPERTY()
	bool bAvailable;

	UPROPERTY()
	float CycleTime;

	FTimerHandle SpawnerCycleTimer;
	
		//...
};
