// Created and developed by Marco Silva


#include "BaseWeapon.h"

#include "BaseCharacter.h"
#include "BasePlayerController.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "ProjectMagna/Statics/MagnaStatics.h"


// Sets replicated variables
void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseWeapon, GameWeaponSettings);
	DOREPLIFETIME(ABaseWeapon, Character);
	DOREPLIFETIME(ABaseWeapon, Player);
}

// Sets default values
ABaseWeapon::ABaseWeapon() :
	bOwner(false),
	bHoldingFire(false),
	bLocked(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InputComponent = CreateDefaultSubobject<UInputComponent>(TEXT("Input Component"));
	SetupPlayerInputComponent(InputComponent);

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));

	const ConstructorHelpers::FObjectFinder<UWeaponData> Asset(TEXT("/Game/Data/Weapons/DA_AK-47.DA_AK-47"));
	if (Asset.Succeeded())
	{
		WeaponData = Asset.Object;
	}

	WeaponData->SetGameWeaponSettings(GameWeaponSettings);
	
	bReplicates = true;
	bAlwaysRelevant = true;
	
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	DisableInput(GetWorld()->GetFirstPlayerController());
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABaseWeapon::InputShootPressed);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABaseWeapon::InputShootReleased);
	
}


void ABaseWeapon::EquipWeapon(const bool bIsOwner)
{
	bOwner = bIsOwner;
	
	if (bIsOwner)
	{
		EnableInput(GetWorld()->GetFirstPlayerController());
	}
	
}

void ABaseWeapon::UnEquipWeapon(const bool bIsOwner)
{
	bOwner = bIsOwner;
	
	if (bIsOwner)
	{
		DisableInput(GetWorld()->GetFirstPlayerController());
	}
	
}

EEquipment ABaseWeapon::GetEquipmentSlot() const
{
	return WeaponData->EquipmentSlot;
}

void ABaseWeapon::StartShooting()
{
	if (!bLocked)
	{
		bLocked = true;
		
		Shoot();
		GetWorldTimerManager().SetTimer(FireTimer, this, &ABaseWeapon::Shoot, WeaponData->GetFinalFireRate(), true);
	}
}

void ABaseWeapon::StopShooting()
{
	GetWorldTimerManager().ClearTimer(FireTimer);
	
}

void ABaseWeapon::Shoot()
{
	CurrentBurst = WeaponData->WeaponFireSettings.NumBursts;
	Burst();
	
	if (WeaponData->IsFullAuto())
		GetWorldTimerManager().SetTimer(BurstTimer, this, &ABaseWeapon::Burst, WeaponData->GetBurstRate(), true);

	GetWorldTimerManager().SetTimer(LockTimer, this, &ABaseWeapon::UnlockWeapon, WeaponData->GetFinalFireRate(), false);
	
}

void ABaseWeapon::Burst()
{
	CurrentBurst--;
	Attack();
	GEngine->AddOnScreenDebugMessage(-1, 1.0, TEAM_COLOR_HEROES, TEXT("Player is shooting his weapon"));

	if (CurrentBurst == 0)
	{
		GetWorldTimerManager().ClearTimer(BurstTimer);
	}
}

void ABaseWeapon::Attack() const
{
	FVector StartLocation = Player->PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + UKismetMathLibrary::GetForwardVector(Player->PlayerCameraManager->GetCameraRotation()) * 5000.0f;
	FCollisionQueryParams TraceParams;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.bTraceComplex = false;

	FHitResult Result(ForceInit);
	bool bBlocked = GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECC_Visibility, TraceParams);

	if (bBlocked)
	{
		IInteractionInterface* Interface = Cast<IInteractionInterface>(Result.GetActor());
		if (Interface)
		{
			FDamageData DamageData;
			DamageData.Damage = WeaponData->Damage;
			Player->ServerDamageEntity(Result.GetActor(), DamageData);
		}
	}
}


void ABaseWeapon::UnlockWeapon()
{
	bLocked = false;
}


void ABaseWeapon::InputShootPressed()
{
	bHoldingFire = true;
	StartShooting();
}

void ABaseWeapon::InputShootReleased()
{
	bHoldingFire = false;
	StopShooting();
}

