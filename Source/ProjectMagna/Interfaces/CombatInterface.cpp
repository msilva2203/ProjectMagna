// Created and developed by Marco Silva


#include "CombatInterface.h"


// Add default functionality here for any ICombatInterface functions that are not pure virtual.

void ICombatInterface::Damage(AActor* DamageInstigator, FDamageData Damage)
{
}

void ICombatInterface::SetEntitySpotted(const bool bSpotted, const bool bImmediate)
{
}

float ICombatInterface::GetCurrentHealth()
{
	return 0.0;
}

float ICombatInterface::GetMaxHealth()
{
	return 0.0;
}

AActor* ICombatInterface::GetInstigatorPawn()
{
	return nullptr;
}
