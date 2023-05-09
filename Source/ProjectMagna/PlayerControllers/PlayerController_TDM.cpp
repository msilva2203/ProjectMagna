// Created and developed by Marco Silva


#include "PlayerController_TDM.h"

#include "ProjectMagna/GameStates/GameState_TDM.h"


// Sets default values
APlayerController_TDM::APlayerController_TDM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Gamemode = EGamemode::Tdm;
}

// Called when the game starts or when spawned
void APlayerController_TDM::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() < NM_Client)
	{
		GameState_TDM = Cast<AGameState_TDM>(GetWorld()->GetGameState());
	}
	
}

// Called every frame
void APlayerController_TDM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerController_TDM::SetupPlayer_Implementation()
{
	Super::SetupPlayer_Implementation();

	CreateGameHUD();
	HideGameHUD();
}

void APlayerController_TDM::StartPlayer_Implementation()
{
	Super::StartPlayer_Implementation();

	ShowGameHUD();
	ShowPlayerHUD();
}


void APlayerController_TDM::ShowGameHUD()
{
	Super::ShowGameHUD();
	
	if (!IsValid(GameHUD_TDM)) return;
	GameHUD_TDM->SetVisibility(ESlateVisibility::Visible);
}

void APlayerController_TDM::HideGameHUD()
{
	Super::HideGameHUD();
	
	if (!IsValid(GameHUD_TDM)) return;
	GameHUD_TDM->SetVisibility(ESlateVisibility::Collapsed);
}

void APlayerController_TDM::OnPlayerKill(AActor* KilledActor)
{
	Super::OnPlayerKill(KilledActor);
	
	GameState_TDM->OffsetTeamScore(GetTeam(), 1);
}

UGameHUD_TDM* APlayerController_TDM::GetGameHUD()
{
	return GameHUD_TDM;
}
