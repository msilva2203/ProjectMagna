// Created and developed by Marco Silva


#include "WeaponData.h"

void UWeaponData::SetGameWeaponSettings(FGameWeaponSettings InGameWeaponSettings)
{
	MaxWeaponState.Mag *= InGameWeaponSettings.MagMultiplier;
	MaxWeaponState.Reserves *= InGameWeaponSettings.ReservesMultiplier;
	DefaultWeaponState.Mag *= InGameWeaponSettings.MagMultiplier;
	DefaultWeaponState.Reserves *= InGameWeaponSettings.ReservesMultiplier;

	Damage *= InGameWeaponSettings.DamageMultiplier;
	CriticalMultiplier *= InGameWeaponSettings.CriticalMultiplier;
	
}

float UWeaponData::GetFinalFireRate() const
{
	return WeaponFireSettings.FireRate + (WeaponFireSettings.NumBursts-1) * WeaponFireSettings.BurstRate;
}

float UWeaponData::GetBurstRate() const
{
	return WeaponFireSettings.BurstRate;
}

int32 UWeaponData::GetNumBursts() const
{
	return WeaponFireSettings.NumBursts;
}

bool UWeaponData::IsFullAuto() const
{
	return WeaponFireSettings.bIsAutomatic;
}
