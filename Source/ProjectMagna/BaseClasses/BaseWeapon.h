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

	UFUNCTION()
	void Reload();
	
	UFUNCTION()
	void UpdateWeaponState();

	UFUNCTION()
	void DropWeapon();

	UFUNCTION(Server, Reliable)
	void ServerSetWeaponState(const FWeaponState NewState);

	UFUNCTION()
	void AddAmmo(int32 Ammo);

	UFUNCTION()
	bool IsEmpty();

	UFUNCTION()
	void OnRep_WeaponState();



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	UWeaponData* WeaponData;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponState)
	FWeaponState WeaponState;

	UPROPERTY()
	int32 CurrentMag;

	UPROPERTY()
	int32 CurrentReserves;

	UPROPERTY()
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY()
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
