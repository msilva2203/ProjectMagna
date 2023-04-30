// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna.h"
#include "Engine/GameInstance.h"
#include "MagnaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UMagnaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<FGameSetting> GameSettings;
	
};
