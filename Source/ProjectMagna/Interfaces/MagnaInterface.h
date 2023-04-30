// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/ProjectMagna.h"
#include "UObject/Interface.h"
#include "MagnaInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMagnaInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTMAGNA_API IMagnaInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ETeam GetTeam();
	virtual FText GetMagnaPlayerName();
	
};
