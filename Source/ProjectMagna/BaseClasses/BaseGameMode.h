// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "PlayerSpawner.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectMagna/MagnaGameInstance.h"
#include "ProjectMagna/Data/WeaponData.h"
#include "BaseGameMode.generated.h"


// Forward Declarations
class AWeaponPickup;

UCLASS()
class PROJECTMAGNA_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	//
	// Methods
	//

	virtual void StartGame();
	virtual void EndGame();
	virtual void GameTimeCallback();
	virtual void HandleGameSettings(FString SettingName, int32 SelectedOption);
	
	void SpawnPlayers(const TArray<ABasePlayerController*>& PlayersToSpawn, bool bUsePlayerTeam = false);
	void RemoveCharacter(ABaseCharacter* Character);
	void SetPlayerTeam(APlayerController* Player) const;
	ETeam FindAvailableTeam() const;

	TArray<APlayerSpawner*> FindAvailableSpawners(const ETeam SpawnerTeam);

	bool IsFriendlyFireActive() const { return MatchSettings.bFriendlyFire; }
	int32 GetRespawnTime() const { return MatchSettings.RespawnTime; }

	UWeaponData* GetWeaponData(uint8 InWeaponID);

		//...

	//
	// Properties
	//
	
	UPROPERTY()
	UMagnaGameInstance* MagnaGameInstance;

	UPROPERTY()
	FMatchSettings MatchSettings;

	UPROPERTY()
	int32 NumTeams;

	UPROPERTY()
	int32 MinPlayers;

	UPROPERTY()
	TArray<APlayerSpawner*> PlayerSpawners;

	UPROPERTY()
	TArray<AWeaponPickup*> WeaponPickups;
	
	UPROPERTY(BlueprintReadOnly, Category = "Match")
	TArray<ABasePlayerController*> Players;
	
	UPROPERTY()
	TArray<ABaseCharacter*> PlayerCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Data")
	TArray<UWeaponData*> WeaponData;



	UPROPERTY()
	FTimerHandle GameStartTimer;

	UPROPERTY()
	FTimerHandle GameClockTimer;
	
		//...
};
