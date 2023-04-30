// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectMagna/ProjectMagna.h"
#include "ProjectMagna/Data/WeaponData.h"
#include "BaseWeapon.generated.h"

// Forward Declarations
class ABaseCharacter;
class ABasePlayerController;


UCLASS()
class PROJECTMAGNA_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void EquipWeapon(const bool bIsOwner);

	UFUNCTION()
	void UnEquipWeapon(const bool bIsOwner);

	UFUNCTION()
	EEquipment GetEquipmentSlot() const;

	UFUNCTION()
	void StartShooting();

	UFUNCTION()
	void StopShooting();

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void Burst();

	UFUNCTION()
	void UnlockWeapon();

	UFUNCTION()
	void Attack() const;



	UPROPERTY()
	UWeaponData* WeaponData;

	UPROPERTY()
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(Replicated)
	ABasePlayerController* Player;

	UPROPERTY(Replicated)
	ABaseCharacter* Character;

	UPROPERTY(Replicated)
	FGameWeaponSettings GameWeaponSettings;

	UPROPERTY()
	bool bOwner;

	UPROPERTY()
	bool bHoldingFire;

	UPROPERTY()
	bool bLocked;
	
	UPROPERTY()
	int32 CurrentBurst;

	UPROPERTY()
	FTimerHandle FireTimer;

	UPROPERTY()
	FTimerHandle BurstTimer;

	UPROPERTY()
	FTimerHandle LockTimer;

	void InputShootPressed();
	void InputShootReleased();
	
};
