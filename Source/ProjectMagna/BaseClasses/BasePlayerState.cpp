// Created and developed by Marco Silva


#include "BasePlayerState.h"

#include "Net/UnrealNetwork.h"

// Sets replicated variables
void ABasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasePlayerState, PlayerTeam);
}

// Sets default values
ABasePlayerState::ABasePlayerState() :
	PlayerTeam(ETeam::None)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	this->MinNetUpdateFrequency = 200.0;
}

// Called when the game starts or when spawned
void ABasePlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayerState::ServerSetTeam_Implementation(const ETeam NewTeam)
{
	PlayerTeam = NewTeam;
}

void ABasePlayerState::OnRep_PlayerTeam()
{
	// On Player Team Replicated
	
}


//
// Interfaces
//

ETeam ABasePlayerState::GetTeam()
{
	return PlayerTeam;
}

FText ABasePlayerState::GetMagnaPlayerName()
{
	const FString Name = "[" + PlayerClanTag.ToString() + "] " + GetPlayerName();
	return FText::FromString(Name);
}

	
	//...
