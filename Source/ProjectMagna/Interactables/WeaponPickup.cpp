// Created and developed by Marco Silva


#include "WeaponPickup.h"

#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectMagna/BaseClasses/BaseWeapon.h"
#include "ProjectMagna/BaseClasses/BaseCharacter.h"
#include "ProjectMagna/BaseClasses/BasePlayerController.h"
#include "ProjectMagna/Statics/MagnaStatics.h"

AWeaponPickup::AWeaponPickup() :
	WeaponID(0),
	bPersistent(false)
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	TArray<FString> DebugString;
	DebugString.Add("Weapon: " + UMagnaStatics::GetWeaponName(WeaponID).ToString());
	DebugString.Add("Active: " + UKismetStringLibrary::Conv_BoolToString(IsActive()));
	if (GetNetMode() < NM_Client)
	{
		DebugString.Add("Mag State: " + FString::FromInt(WeaponState.Mag));
		DebugString.Add("Reserves State: " + FString::FromInt(WeaponState.Reserves));
	}
	
	UMagnaStatics::DrawDebugStringLines(this, GetActorLocation(), DebugString, FLinearColor::Red);
}


void AWeaponPickup::Interact(ABasePlayerController* PlayerController)
{
	Super::Interact(PlayerController);

	if (IsActive())
	{
		ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());
		if (IsValid(PlayerCharacter))
		{
			ABaseWeapon* CurrentPlayerWeapon = PlayerCharacter->GetPlayerWeapon(EquipmentSlot);

			if (IsValid(CurrentPlayerWeapon))
			{
				if (CurrentPlayerWeapon->WeaponData->WeaponID != WeaponID)
				{
					CurrentPlayerWeapon->DropWeapon();
					PlayerCharacter->ServerPickupWeapon(WeaponID);
				}
				else
				{
					CurrentPlayerWeapon->K2_DestroyActor();
					PlayerCharacter->ServerPickupWeapon(WeaponID);
				}
			}
			else
			{
				PlayerCharacter->ServerPickupWeapon(WeaponID);
			}
		}

		if (IsPersistent())
		{
			SetActive(false);
		}
		else
		{
			K2_DestroyActor();
		}
	}
}


bool AWeaponPickup::IsPersistent() const
{
	return this->bPersistent;
}

