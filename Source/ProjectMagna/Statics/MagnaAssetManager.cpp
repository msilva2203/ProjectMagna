// Created and developed by Marco Silva


#include "MagnaAssetManager.h"

// Asset Types
const FPrimaryAssetType UMagnaAssetManager::WeaponType = TEXT("Weapons");

	//...

void UMagnaAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	
}

UMagnaAssetManager& UMagnaAssetManager::Get()
{
	UMagnaAssetManager* This = Cast<UMagnaAssetManager>(GEngine->AssetManager);

	if (This)
	{
		return *This;
	}

	return *NewObject<UMagnaAssetManager>();
}

