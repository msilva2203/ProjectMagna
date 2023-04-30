// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MagnaAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UMagnaAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Default Constructor
	UMagnaAssetManager() {}
	
	// Asset Types
	static const FPrimaryAssetType WeaponType;

	// Initial Loading
	virtual void StartInitialLoading() override;

	static UMagnaAssetManager& Get();
	
};
