// Created and developed by Marco Silva


#include "BasePlayerController.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "ArenaCamera.h"
#include "BaseGameMode.h"
#include "BaseInteractable.h"
#include "Net/UnrealNetwork.h"
#include "ProjectMagna/Statics/MagnaStatics.h"


void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABasePlayerController, CurrentDeathInstigator);
	
}

// Sets default values
ABasePlayerController::ABasePlayerController() :
	bHasStarted(false),
	Gamemode(EGamemode::None),
	PlayerGameState(EPlayerGameState::Spectating)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetNetMode() < NM_Client)
	{
		AuthGameMode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());
	}

	if (IsLocalPlayerController())
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this, AArenaCamera::StaticClass(), Actors);
		for (const auto Actor : Actors)
		{
			AArenaCamera* Camera = Cast<AArenaCamera>(Actor);
			if (IsValid(Camera))
			{
				ArenaCameras.Add(Camera);
			}
		}
		CurrentCameraIndex = FMath::RandRange(0, ArenaCameras.Num()-1);
		SpectateArenaCamera(CurrentCameraIndex, true);

		DeathCamera = GetWorld()->SpawnActor<ADeathCamera>(ADeathCamera::StaticClass());
	}
	
}

// Called every frame
void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("NextCamera", IE_Pressed, this, &ABasePlayerController::InputNextCameraPressed);
	InputComponent->BindAction("PreviousCamera", IE_Pressed, this, &ABasePlayerController::InputPreviousCameraPressed);
	InputComponent->BindAction("NextPlayer", IE_Pressed, this, &ABasePlayerController::InputNextPlayerPressed);
	InputComponent->BindAction("PreviousPlayer", IE_Pressed, this, &ABasePlayerController::InputPreviousPlayerPressed);
	
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (IsValid(CurrentPawn))
	{
		AuthGameMode->RemoveCharacter(Cast<ABaseCharacter>(CurrentPawn));
		CurrentPawn->K2_DestroyActor();
	}
	
	CurrentPawn = InPawn;
}

void ABasePlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	
	ClientOnUnPossess();
}

void ABasePlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}


void ABasePlayerController::ClientOnPossess_Implementation()
{
	DeathCamera->SetActive(false);
	
}


void ABasePlayerController::ClientOnUnPossess_Implementation()
{
	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 0.0;

	DeathCamera->SetActive(true);
	const FVector CameraLocation = this->PlayerCameraManager->GetCameraLocation();
	const FRotator CameraRotation = this->PlayerCameraManager->GetCameraRotation();
	DeathCamera->CameraComponent->SetWorldRotation(CameraRotation);
	DeathCamera->SetActorLocation(CameraLocation);
	
	this->SetViewTarget(DeathCamera, TransitionParams);
}

void ABasePlayerController::ShowGameHUD()
{
}

void ABasePlayerController::HideGameHUD()
{
}

void ABasePlayerController::ShowPauseMenu()
{
	HideGameHUD();
	
}

void ABasePlayerController::HidePauseMenu()
{
	ShowGameHUD();
	
}

void ABasePlayerController::ShowPlayerHUD()
{
	
}

void ABasePlayerController::HidePlayerHUD()
{
	
}

void ABasePlayerController::ShowScoreboard()
{
	HideGameHUD();
	
}

void ABasePlayerController::HideScoreboard()
{
	ShowGameHUD();
	
}


void ABasePlayerController::SetupPlayer_Implementation()
{
}

void ABasePlayerController::StartPlayer_Implementation()
{
	bHasStarted = true;
	
}


void ABasePlayerController::SetPlayerGameState(const EPlayerGameState NewState)
{
	PlayerGameState = NewState;

	if (PlayerGameState == EPlayerGameState::Playing)
	{
		if (GetWorldTimerManager().IsTimerActive(SpectatingUpdateTimer))
			GetWorldTimerManager().ClearTimer(SpectatingUpdateTimer);
	}
}

bool ABasePlayerController::IsPlaying() const
{
	return PlayerGameState == EPlayerGameState::Playing;
}

bool ABasePlayerController::IsSpectating() const
{
	return PlayerGameState == EPlayerGameState::Spectating;
}

void ABasePlayerController::SpectateArenaCamera(int32 CameraIndex, const bool bForceSpectate)
{
	CameraIndex = FMath::Clamp(CameraIndex, 0, ArenaCameras.Num()-1);
	
	if (CameraIndex != CurrentCameraIndex || bForceSpectate)
	{
		CurrentCameraIndex = CameraIndex;
		if (CurrentCameraIndex >= 0 && CurrentCameraIndex < ArenaCameras.Num())
		{
			ArenaCameras[CurrentCameraIndex]->SpectateCamera();
			bSpectatingPlayer = false;
		}
	}
	
}

void ABasePlayerController::AddTeammate(ABaseCharacter* TeammateCharacter)
{
	if (!Teammates.Contains(TeammateCharacter))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0, TEAM_COLOR_HEROES, TEXT("Teammate added"));
		Teammates.Add(TeammateCharacter);
	}
	
}

void ABasePlayerController::RemoveTeammate(ABaseCharacter* TeammateCharacter)
{
	if (Teammates.Contains(TeammateCharacter))
	{
		Teammates.Remove(TeammateCharacter);
		if (TeammateCharacter->bIsSpectated)
		{
			TeammateCharacter->SetSpectating(false);
		}
		GEngine->AddOnScreenDebugMessage(-1, 1.0, TEAM_COLOR_HEROES, TEXT("Teammate removed"));
		
		if (IsSpectating())
		{
			if (bSpectatingPlayer)
				if (!SpectateTeammate(CurrentTeammateIndex, true))
					SpectateArenaCamera(CurrentCameraIndex, true);
		}
	}
	
}

bool ABasePlayerController::SpectateTeammate(int32 TeammateIndex, const bool bForceSpectate)
{
	if (Teammates.IsEmpty())
		return false;

	TeammateIndex = FMath::Clamp(TeammateIndex, 0, Teammates.Num()-1);
	
	if (TeammateIndex != CurrentTeammateIndex || bForceSpectate)
	{
		ABaseCharacter* SpectatingPlayer = Teammates[CurrentTeammateIndex];
		if (IsValid(SpectatingPlayer))
		{
			SpectatingPlayer->SetSpectating(false);
		}
		
		CurrentTeammateIndex = TeammateIndex;
		if (!IsValid(Teammates[CurrentTeammateIndex]))
			return false;
		Teammates[CurrentTeammateIndex]->SetSpectating(true);

		this->bSpectatingPlayer = true;
		return true;
	}
	
	return false;
}

void ABasePlayerController::ServerDamageEntity_Implementation(AActor* Entity, FDamageData Damage)
{
	ICombatInterface* Interface = Cast<ICombatInterface>(Entity);
	if (Interface)
	{
		Interface->Damage(this, Damage);
	}
}

void ABasePlayerController::OnPlayerKill(AActor* KilledActor)
{
	GetPlayerState<ABasePlayerState>()->OffsetKills(1);
}

void ABasePlayerController::OnPlayerAssist(AActor* AssistedActor)
{
	GetPlayerState<ABasePlayerState>()->OffsetAssists(1);
}

void ABasePlayerController::OnPlayerDeath(AActor* DeathInstigator)
{
	GetPlayerState<ABasePlayerState>()->OffsetDeaths(1);

	ICombatInterface* Interface = Cast<ICombatInterface>(DeathInstigator);

	if (Interface)
	{
		CurrentDeathInstigator = Interface->GetInstigatorPawn();
		if (GetWorld()->GetNetMode() == NM_ListenServer && IsLocalPlayerController())
			DeathCamera->SetDeathInstigator(CurrentDeathInstigator);
	
		const int32 Time = AuthGameMode->GetRespawnTime();
	
		StartServerRespawnTimer(Time);
		ClientOnPlayerDeath(Time);
	}
}

void ABasePlayerController::ClientOnPlayerDeath_Implementation(int32 Time)
{
	UnPossess();
	StartClientRespawnTimer(Time);
	SetPlayerGameState(EPlayerGameState::Spectating);
	
	GetWorldTimerManager().SetTimer(SpectatingUpdateTimer, this, &ABasePlayerController::UpdateSpectating, 3.0, false);
	
}

void ABasePlayerController::StartServerRespawnTimer(int32 Time)
{
	GetWorldTimerManager().SetTimer(ServerRespawnTimer, this, &ABasePlayerController::RespawnPlayer, Time, false);
}

void ABasePlayerController::StartClientRespawnTimer(int32 Time)
{
	this->RespawnTime = Time;
	GetWorldTimerManager().SetTimer(ClientRespawnTimer, this, &ABasePlayerController::UpdateRespawnTime, 1.0, true);
}

void ABasePlayerController::RespawnPlayer()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, TEXT("Player respawned!!!"));
	
	TArray<ABasePlayerController*> Players;
	Players.Add(this);
	AuthGameMode->SpawnPlayers(Players);
}

void ABasePlayerController::UpdateRespawnTime()
{
	this->RespawnTime--;
	this->RespawnTime = FMath::Clamp(RespawnTime, 0, 50);
	
}

void ABasePlayerController::OnRep_CurrentDeathInstigator()
{
	DeathCamera->SetDeathInstigator(CurrentDeathInstigator);
}

void ABasePlayerController::UpdateSpectating()
{
	if (!Teammates.IsEmpty())
	{
		if (!SpectateTeammate(CurrentTeammateIndex, true))
			SpectateArenaCamera(CurrentCameraIndex, true);
	}
	else
	{
		SpectateArenaCamera(CurrentCameraIndex, true);
	}
}

void ABasePlayerController::ServerInteract_Implementation(ABaseInteractable* InInteractable)
{
	InInteractable->Interact(this);
}



ETeam ABasePlayerController::GetTeam()
{
	IMagnaInterface* Interface = Cast<IMagnaInterface>(PlayerState);

	if (Interface)
	{
		return Interface->GetTeam();
	}
	return ETeam::None;
}

FText ABasePlayerController::GetMagnaPlayerName()
{
	IMagnaInterface* Interface = Cast<IMagnaInterface>(PlayerState);

	if (Interface)
	{
		return Interface->GetMagnaPlayerName();
	}
	return FText::FromString("Magna Player");
}

AActor* ABasePlayerController::GetInstigatorPawn()
{
	return CurrentPawn;
}



void ABasePlayerController::InputNextCameraPressed()
{
	if (IsSpectating())
	{
		int32 NewIndex = (CurrentCameraIndex + 1) % ArenaCameras.Num();
		SpectateArenaCamera(NewIndex);
	}
}

void ABasePlayerController::InputPreviousCameraPressed()
{
	if (IsSpectating())
	{
		int32 NewIndex = CurrentCameraIndex - 1;
		
		if (NewIndex >= 0) NewIndex %= ArenaCameras.Num();
		else NewIndex = ArenaCameras.Num() + NewIndex;
		
		SpectateArenaCamera(NewIndex);
	}
}

void ABasePlayerController::InputNextPlayerPressed()
{
	if (IsSpectating() && !Teammates.IsEmpty())
	{
		int32 NewIndex = (CurrentTeammateIndex + 1) % Teammates.Num();
		SpectateTeammate(NewIndex);
	}
}

void ABasePlayerController::InputPreviousPlayerPressed()
{
	if (IsSpectating() && !Teammates.IsEmpty())
	{
		int32 NewIndex = CurrentTeammateIndex - 1;

		if (NewIndex >= 0) NewIndex %= Teammates.Num();
		else NewIndex = Teammates.Num() + NewIndex;

		SpectateTeammate(NewIndex);
	}
}

