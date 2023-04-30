// Created and developed by Marco Silva


#include "WeaponPickup.h"

#include "ProjectMagna/BaseClasses/BaseCharacter.h"
#include "ProjectMagna/BaseClasses/BasePlayerController.h"

AWeaponPickup::AWeaponPickup() :
	Weapon(EWeapon::Default),
	bPersistent(false)
{
	
}

void AWeaponPickup::Interact(ABasePlayerController* PlayerController)
{
	Super::Interact(PlayerController);

	if (IsActive())
	{
		ABaseCharacter* PlayerCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->ServerPickupWeapon(Weapon);
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

