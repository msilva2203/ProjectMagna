// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/ProjectMagna.h"
#include "ProjectMagna/BaseClasses/BaseInteractable.h"
#include "WeaponPickup.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API AWeaponPickup : public ABaseInteractable
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AWeaponPickup();

	virtual void Interact(ABasePlayerController* PlayerController) override;

	UFUNCTION()
	bool IsPersistent() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn), Category = "Weapon Pickup")
	EWeapon Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn))
	bool bPersistent;

	UPROPERTY()
	FWeaponState WeaponState;
};
