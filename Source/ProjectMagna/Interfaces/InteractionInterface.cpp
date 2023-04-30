// Created and developed by Marco Silva


#include "InteractionInterface.h"


// Add default functionality here for any IInteractionInterface functions that are not pure virtual.

void IInteractionInterface::Damage(AActor* DamageInstigator, FDamageData Damage)
{
}

float IInteractionInterface::GetMaxHealth()
{
	return 0.0f;
}

float IInteractionInterface::GetCurrentHealth()
{
	return 0.0f;
}

void IInteractionInterface::SetEntitySpotted(const bool bSpotted, const bool bImmediate)
{
}

void IInteractionInterface::AddInteractable(ABaseInteractable* InInteractable)
{
}

void IInteractionInterface::RemoveInteractable(ABaseInteractable* InInteractable)
{
}

bool IInteractionInterface::IsPlayer()
{
	return false;
}

bool IInteractionInterface::IsLocalPlayer()
{
	return false;
}

void IInteractionInterface::TestEntityInteractables()
{
}

