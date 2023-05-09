// Created and developed by Marco Silva


#include "BaseGameMode.h"

#include "GameFramework/PlayerState.h"
#include "BaseGameState.h"
#include "BasePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectMagna/Data/WeaponData.h"
#include "ProjectMagna/Interactables/WeaponPickup.h"
#include "ProjectMagna/Statics/MagnaAssetManager.h"
#include "ProjectMagna/Statics/MagnaStatics.h"


// Sets default values
ABaseGameMode::ABaseGameMode() :
	NumTeams(2),
	MinPlayers(3)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GameStateClass = ABaseGameState::StaticClass();
	PlayerStateClass = ABasePlayerState::StaticClass();
	PlayerControllerClass = ABasePlayerController::StaticClass();

	MatchSettings.bFriendlyFire = true;
	MatchSettings.RespawnTime = 10;
	MatchSettings.WeaponSettings.MagMultiplier = 1.0;
	MatchSettings.WeaponSettings.ReservesMultiplier = 1.0;
	MatchSettings.WeaponSettings.DamageMultiplier = 1.0;
	MatchSettings.WeaponSettings.CriticalMultiplier = 1.0;

	TArray<FString> Paths;
	Paths.Add(TEXT("/Game/Data/Weapons/DA_AK-47.DA_AK-47"));
	Paths.Add(TEXT("/Game/Data/Weapons/DA_FS-92.DA_FS-92"));
	
	for (const auto Path : Paths)
	{
		ConstructorHelpers::FObjectFinder<UWeaponData> Asset(Path.GetCharArray().GetData());
		if (Asset.Succeeded())
		{
			WeaponData.Add(Asset.Object);
		}
	}
		
}

// Called when the game starts or when spawned
void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = GetWorld()->GetGameInstance();
	MagnaGameInstance = Cast<UMagnaGameInstance>(GameInstance);

	if (IsValid(MagnaGameInstance))
	{
		for (const FGameSetting Setting : MagnaGameInstance->GameSettings)
		{
			HandleGameSettings(Setting.SettingName, Setting.SelectedOption);
		}
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerSpawner::StaticClass(), Actors);

	for (const auto Actor : Actors)
	{
		PlayerSpawners.Add(Cast<APlayerSpawner>(Actor));
	}

	UGameplayStatics::GetAllActorsOfClass(this, AWeaponPickup::StaticClass(), Actors);
	for (const auto Actor : Actors)
	{
		AWeaponPickup* Pickup = Cast<AWeaponPickup>(Actor);
		if (IsValid(Pickup))
		{
			if (Pickup->IsPersistent())
			{
				WeaponPickups.Add(Pickup);
				Pickup->WeaponState = GetWeaponData(Pickup->WeaponID)->DefaultWeaponState;
				Pickup->SetActive(true);
			}
		}
	}
	
}

// Called every frame
void ABaseGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABaseGameMode::HandleGameSettings(FString SettingName, int32 SelectedOption)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Blue, SettingName);
	
}


void ABaseGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	ABasePlayerController* Player = Cast<ABasePlayerController>(NewPlayer);
	
	if (IsValid(Player))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Cyan, TEXT("New player joined the game!"));
		Players.Add(Player);
		SetPlayerTeam(Player);
		Player->SetupPlayer();
	}

	if (!GetWorldTimerManager().IsTimerActive(GameStartTimer))
	{
		GetWorldTimerManager().SetTimer(GameStartTimer, this, &ABaseGameMode::StartGame, 5.0, false);
	}
}

void ABaseGameMode::Logout(AController* Exiting)
{
	ABasePlayerController* Player = Cast<ABasePlayerController>(Exiting);

	if (Players.Contains(Player))
	{
		Players.Remove(Player);
	}
}

void ABaseGameMode::StartGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Yellow, TEXT("Game Started"));
	GetWorldTimerManager().SetTimer(GameClockTimer, this, &ABaseGameMode::GameTimeCallback, 1.0, true);
	SpawnPlayers(Players, true);
	
}

void ABaseGameMode::EndGame()
{
	
}

void ABaseGameMode::SpawnPlayers(const TArray<ABasePlayerController*>& PlayersToSpawn, bool bUsePlayerTeam)
{
	for (auto Player : PlayersToSpawn)
	{
		TArray<APlayerSpawner*> Spawners = FindAvailableSpawners(bUsePlayerTeam ? Player->GetTeam() : ETeam::None);
		const int32 Index = FMath::RandRange(0, Spawners.Num()-1);
		
		ABaseCharacter* NewCharacter = Spawners[Index]->SpawnPlayer(Player);
		this->PlayerCharacters.Add(NewCharacter);

		if (!Player->bHasStarted)
		{
			Player->StartPlayer();
		}
	}
}

void ABaseGameMode::RemoveCharacter(ABaseCharacter* Character)
{
	if (PlayerCharacters.Contains(Character))
	{
		PlayerCharacters.Remove(Character);
	}
}


void ABaseGameMode::SetPlayerTeam(APlayerController* Player) const
{
	ABasePlayerState* PlayerState = Cast<ABasePlayerState>(Player->PlayerState);
	PlayerState->ServerSetTeam(FindAvailableTeam());
	
}

ETeam ABaseGameMode::FindAvailableTeam() const
{
	TArray<int32> Sizes;
	for (int i = 0; i < NumTeams; i++)
	{
		Sizes.Add(0);
	}

	for (auto Player : Players)
	{
		if (Player->GetTeam() != ETeam::None)
		{
			const int32 Index = static_cast<int32>(Player->GetTeam()) - 1;
			Sizes[Index]++;
		}
	}

	int32 Index = 0;
	int32 Size = Sizes[0];
	for (int i = 1; i < Sizes.Num(); i++)
	{
		if (Sizes[i] < Size)
		{
			Index = i;
			Size = Sizes[i];
		}
	}

	return static_cast<ETeam>(Index + 1);
}


TArray<APlayerSpawner*> ABaseGameMode::FindAvailableSpawners(const ETeam SpawnerTeam)
{
	TArray<APlayerSpawner*> Spawners;
	for (const auto Spawner : PlayerSpawners)
	{
		if (Spawner->IsAvailable() && (Spawner->GetTeam() == SpawnerTeam || SpawnerTeam == ETeam::None))
		{
			Spawners.Add(Spawner);
		}
	}

	return Spawners;
}

UWeaponData* ABaseGameMode::GetWeaponData(uint8 InWeaponID)
{
	InWeaponID = FMath::Clamp<uint8>(InWeaponID, 0, WeaponData.Num());
	
	for (const auto Data : WeaponData)
	{
		if (Data->WeaponID == InWeaponID)
			return Data;
	}

	return WeaponData[0];
}

void ABaseGameMode::GameTimeCallback()
{
}
