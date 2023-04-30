// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectMagna/ProjectMagna.h"
#include "WeaponData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UWeaponData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	EWeapon Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	EEquipment EquipmentSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	ETier WeaponTier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	float CriticalMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	FWeaponFireSettings WeaponFireSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	FWeaponState MaxWeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	FWeaponState DefaultWeaponState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data")
	FCameraSettings ZoomCameraSettings;

	//
	//	Methods
	//

	UFUNCTION()
	void SetGameWeaponSettings(FGameWeaponSettings InGameWeaponSettings);

	UFUNCTION()
	float GetFinalFireRate() const;

	UFUNCTION()
	float GetBurstRate() const;

	UFUNCTION()
	int32 GetNumBursts() const;

	UFUNCTION()
	bool IsFullAuto() const;
	
};
