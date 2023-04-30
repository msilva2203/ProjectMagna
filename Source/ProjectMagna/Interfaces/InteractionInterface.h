// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/ProjectMagna.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// Forward Declarations
class ABaseInteractable;

// This class does not need to be modified.
UINTERFACE()
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTMAGNA_API IInteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Damage(AActor* DamageInstigator, FDamageData Damage);
	virtual float GetMaxHealth();
	virtual float GetCurrentHealth();
	virtual void SetEntitySpotted(const bool bSpotted, const bool bImmediate);
	virtual void AddInteractable(ABaseInteractable* InInteractable);
	virtual void RemoveInteractable(ABaseInteractable* InInteractable);
	virtual bool IsPlayer();
	virtual bool IsLocalPlayer();
	virtual void TestEntityInteractables();
};
