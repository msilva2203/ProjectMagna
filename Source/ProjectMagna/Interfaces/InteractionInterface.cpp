// Created and developed by Marco Silva


#include "InteractionInterface.h"


// Add default functionality here for any IInteractionInterface functions that are not pure virtual.

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

