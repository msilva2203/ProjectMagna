// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerState.h"
#include "DeathCamera.h"
#include "MovieSceneFwd.h"
#include "GameFramework/PlayerController.h"
#include "ProjectMagna/ProjectMagna.h"
#include "ProjectMagna/Interfaces/CombatInterface.h"
#include "ProjectMagna/Interfaces/MagnaInterface.h"
#include "BasePlayerController.generated.h"


// Forward declarations
class ABaseCharacter;
class AArenaCamera;
class ABaseGameMode;
class ABaseInteractable;


UCLASS()
class PROJECTMAGNA_API ABasePlayerController : public APlayerController, public IMagnaInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void OnRep_PlayerState() override;

	UFUNCTION(Client, Reliable)
	void ClientOnPossess();
	
	UFUNCTION(Client, Reliable)
	void ClientOnUnPossess();

	UFUNCTION()
	virtual void ShowGameHUD();

	UFUNCTION()
	virtual void HideGameHUD();

	UFUNCTION()
	void ShowPauseMenu();

	UFUNCTION()
	void HidePauseMenu();

	UFUNCTION()
	void ShowPlayerHUD();

	UFUNCTION()
	void HidePlayerHUD();

	UFUNCTION()
	virtual void ShowScoreboard();

	UFUNCTION()
	virtual void HideScoreboard();

	UFUNCTION(Client, Reliable)
	virtual void SetupPlayer();

	UFUNCTION(Client, Reliable)
	virtual void StartPlayer();

	//
	// Methods
	//

	UFUNCTION()
	bool IsPlaying() const;

	UFUNCTION()
	bool IsSpectating() const;

	UFUNCTION()
	void SpectateArenaCamera(int32 CameraIndex, const bool bForceSpectate = false);

	UFUNCTION()
	void AddTeammate(ABaseCharacter* TeammateCharacter);

	UFUNCTION()
	void RemoveTeammate(ABaseCharacter* TeammateCharacter);

	UFUNCTION()
	bool SpectateTeammate(int32 TeamMateIndex, const bool bForceSpectate = false);

	UFUNCTION()
	void SetPlayerGameState(const EPlayerGameState NewState);

	UFUNCTION(Server, Reliable)
	void ServerDamageEntity(AActor* Entity, FDamageData Damage);

	UFUNCTION()
	virtual void OnPlayerKill(AActor* KilledActor);

	UFUNCTION()
	virtual void OnPlayerAssist(AActor* AssistedActor);

	UFUNCTION()
	virtual void OnPlayerDeath(AActor* DeathInstigator);

	UFUNCTION(Client, Reliable)
	void ClientOnPlayerDeath(int32 Time);

	UFUNCTION()
	void StartServerRespawnTimer(int32 Time);

	UFUNCTION()
	void StartClientRespawnTimer(int32 Time);

	UFUNCTION()
	void RespawnPlayer();

	UFUNCTION()
	void UpdateRespawnTime();

	UFUNCTION()
	void OnRep_CurrentDeathInstigator();

	UFUNCTION()
	void UpdateSpectating();

	UFUNCTION(Server, Reliable)
	void ServerInteract(ABaseInteractable* InInteractable);

		//...

	//
	// Properties
	//

	UPROPERTY()
	ABaseGameMode* AuthGameMode;

	UPROPERTY()
	bool bHasStarted;

	UPROPERTY()
	TArray<AArenaCamera*> ArenaCameras;

	UPROPERTY()
	TArray<ABaseCharacter*> Teammates;

	UPROPERTY()
	ADeathCamera* DeathCamera;

	UPROPERTY()
	APawn* CurrentPawn;

	UPROPERTY()
	EGamemode Gamemode;

	UPROPERTY()
	int32 CurrentCameraIndex;

	UPROPERTY()
	int32 CurrentTeammateIndex;

	UPROPERTY()
	bool bSpectatingPlayer;

	UPROPERTY()
	EPlayerGameState PlayerGameState;

	UPROPERTY()
	int32 RespawnTime;

	UPROPERTY(Replicatedusing = OnRep_CurrentDeathInstigator)
	AActor* CurrentDeathInstigator;



	UPROPERTY()
	FTimerHandle ServerRespawnTimer;

	UPROPERTY()
	FTimerHandle ClientRespawnTimer;

	UPROPERTY()
	FTimerHandle SpectatingUpdateTimer;

		//...

	//
	// Interfaces
	//

	ETeam GetTeam() override;
	FText GetMagnaPlayerName() override;
	AActor* GetInstigatorPawn() override;
	
		//...

	//
	// Input
	//

	void InputNextCameraPressed();
	void InputPreviousCameraPressed();
	void InputNextPlayerPressed();
	void InputPreviousPlayerPressed();
};
