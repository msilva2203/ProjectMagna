// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ProjectMagna.generated.h"


//
// Enumerations
//

UENUM(BlueprintType)
enum class EGamemode: uint8
{
	None		UMETA(DisplayName = "NONE"),
	Tdm			UMETA(DisplayName = "TDM"),
	Ffa			UMETA(DisplayName = "FFA"),
	Ttdm		UMETA(DisplayName = "TTDM"),
	Elim		UMETA(DisplayName = "ELIM")
};

// Team enumeration
UENUM(BlueprintType)
enum class ETeam : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Team01		UMETA(DisplayName = "TEAM01"),
	Team02		UMETA(DisplayName = "TEAM02"),
	Team03		UMETA(DisplayName = "TEAM03"),
	Team04		UMETA(DisplayName = "TEAM04"),
	Team05		UMETA(DisplayName = "TEAM05"),
	Team06		UMETA(DisplayName = "TEAM06"),
	Team07		UMETA(DisplayName = "TEAM07"),
	Team08		UMETA(DisplayName = "TEAM08"),
	Enemy		UMETA(DisplayName = "ENEMY")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Default		UMETA(DisplayName = "DEFAULT"),
	Sprinting	UMETA(DisplayName = "SPRINTING"),
	Aiming		UMETA(DisplayName = "AIMING")
};

UENUM(BlueprintType)
enum class EPlayerGameState : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Playing		UMETA(DisplayName = "PLAYING"),
	Spectating	UMETA(DisplayName = "SPECTATING")
};

UENUM(BlueprintType)
enum class EEquipment : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Secondary	UMETA(DisplayName = "SECONDARY"),
	Primary		UMETA(DisplayName = "PRIMARY")
};

UENUM(BlueprintType)
enum class EShoulder : uint8
{
	Center		UMETA(DisplayName = "CENTER"),
	Right		UMETA(DisplayName = "RIGHT"),
	Left		UMETA(DisplayName = "LEFT")
};

UENUM(BlueprintType)
enum class EWeapon : uint8
{
	Default		UMETA(DisplayName = "Default"),
	AK47		UMETA(DisplayName = "AK-47"),
	FS92		UMETA(DisplayName = "FS-92")
};

UENUM(BlueprintType)
enum class ETier : uint8
{
	Tier1		UMETA(DisplayName = "TIER1"),
	Tier2		UMETA(DisplayName = "TIER2"),
	Tier3		UMETA(DisplayName = "TIER3")
};

	//...

//
// Structs
//

USTRUCT(BlueprintType)
struct FGameSetting
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FString SettingName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FString SettingDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		TArray<FString> Options;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		int32 SelectedOption;
};

USTRUCT(BlueprintType)
struct FGamemodeData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FText GamemodeName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FText GamemodeDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		TArray<FGameSetting> GamemodeSettings;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		TArray<FName> GamemodeMaps;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FString GamemodeUnrealAlias;
};

USTRUCT(BlueprintType)
struct FGameMap : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FText MapName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FText MapDescription;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FName MapName_Unreal;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		UTexture2D* MapDisplayImage;
};

USTRUCT(BlueprintType)
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float Damage;
};

USTRUCT(BlueprintType)
struct FCameraSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float CameraLength;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float CameraHeight;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float TransitionTime;
};

USTRUCT(BlueprintType)
struct FShoulderSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float ShoulderOffset;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float TransitionTime;
};

USTRUCT(BlueprintType)
struct FWeaponState
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		int32 Mag;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		int32 Reserves;
};

USTRUCT(BlueprintType)
struct FWeaponFireSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		bool bIsAutomatic;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		int32 NumBursts;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float FireRate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float BurstRate;
};

USTRUCT(BlueprintType)
struct FGameWeaponSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float MagMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float ReservesMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float DamageMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		float CriticalMultiplier;
};

USTRUCT(BlueprintType)
struct FMatchSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		bool bFriendlyFire;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		int32 RespawnTime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyStructs")
		FGameWeaponSettings WeaponSettings;
};

	//...
