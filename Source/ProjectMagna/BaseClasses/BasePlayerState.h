// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ProjectMagna/Interfaces/MagnaInterface.h"
#include "BasePlayerState.generated.h"

UCLASS()
class PROJECTMAGNA_API ABasePlayerState : public APlayerState, public IMagnaInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlayerState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	// Methods
	//
	
	UFUNCTION(Server, Reliable)
	void ServerSetTeam(const ETeam NewTeam);
	
	UFUNCTION()
	void OnRep_PlayerTeam();

	UFUNCTION()
	virtual void OnRep_Kills();

	UFUNCTION()
	virtual void OnRep_Assists();

	UFUNCTION()
	virtual void OnRep_Deaths();

	UFUNCTION()
	virtual void OnRep_PlayerScore();

	UFUNCTION()
	void SetKills(const int32 NewValue);

	UFUNCTION()
	void SetAssists(const int32 NewValue);

	UFUNCTION()
	void SetDeaths(const int32 NewValue);

	UFUNCTION()
	void SetPlayerScore(const int32 NewValue);

	UFUNCTION()
	void OffsetKills(const int32 Offset);

	UFUNCTION()
	void OffsetAssists(const int32 Offset);

	UFUNCTION()
	void OffsetDeaths(const int32 Offset);

	UFUNCTION()
	void OffsetPlayerScore(const int32 Offset);
	
		//...

	//
	// Properties
	//

	UPROPERTY(ReplicatedUsing = OnRep_PlayerTeam)
	ETeam PlayerTeam;

	UPROPERTY()
	FText PlayerClanTag = FText::FromString("DeFy");

	UPROPERTY(ReplicatedUsing = OnRep_Kills)
	int32 Kills;

	UPROPERTY(ReplicatedUsing = OnRep_Assists)
	int32 Assists;

	UPROPERTY(ReplicatedUsing = OnRep_Deaths)
	int32 Deaths;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerScore)
	int32 PlayerScore;
	
		//...

	//
	// Interfaces
	//
	
	virtual ETeam GetTeam() override;
	virtual FText GetMagnaPlayerName() override;
	
		//...
};
