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
	
		//...

	//
	// Properties
	//

	UPROPERTY(ReplicatedUsing = OnRep_PlayerTeam)
	ETeam PlayerTeam;

	UPROPERTY()
	FText PlayerClanTag = FText::FromString("DeFy");
	
		//...

	//
	// Interfaces
	//
	
	virtual ETeam GetTeam() override;
	virtual FText GetMagnaPlayerName() override;
	
		//...
};
