// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectMagna/Interfaces/CombatInterface.h"
#include "ProjectMagna/Interfaces/InteractionInterface.h"
#include "ProjectMagna/Interfaces/MagnaInterface.h"
#include "BaseCharacter.generated.h"


// Forward Declarations
class ABaseGameMode;
class ABaseWeapon;
class ABasePlayerController;
class UPlayerNameplate;


UCLASS()
class PROJECTMAGNA_API ABaseCharacter : public ACharacter, public IMagnaInterface, public IInteractionInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when Player State has been replicated to client
	virtual void OnRep_PlayerState() override;

	//
	// Methods
	//

	UFUNCTION()
	void SetupCharacter();

	UFUNCTION(Server, Reliable)
	void ServerSetActionState(const EActionState NewState, const bool bForceUpdate = false);

	UFUNCTION()
	void SetActionState(const EActionState State, const bool bNewValue);

	UFUNCTION()
	void OnRep_RepActionState();
	
	UFUNCTION()
	void SetDefaultState(const bool bNewValue);

	UFUNCTION()
	void SetSprintingState(const bool bNewValue);
	
	UFUNCTION()
	void SetAimingState(const bool bNewValue);

	UFUNCTION()
	void SetSpectating(const bool bNewValue);

	UFUNCTION()
	void OnSpectatingUpdate();

	UFUNCTION()
	void OnRep_RepEquipment();

	UFUNCTION()
	void OnRep_WeaponPrimary();

	UFUNCTION()
	void OnRep_WeaponSecondary();

	UFUNCTION(Server, Reliable)
	void ServerPickupWeapon(const uint8 WeaponID);

	UFUNCTION(Server, Reliable)
	void ServerEquipWeapon(const EEquipment NewEquipment);

	UFUNCTION()
	void EquipWeapon(const EEquipment NewEquipment, const bool bForce = true, const bool bReplicate = false);

	UFUNCTION()
	ABaseWeapon* GetPlayerWeapon(const EEquipment Equipment);

	UFUNCTION(Server, Reliable)
	void ServerSetShoulder(const EShoulder NewShoulder);

	UFUNCTION()
	void OnRep_Shoulder();

	UFUNCTION()
	void SetShoulder(const EShoulder NewShoulder, const bool bReplicate = false);

	UFUNCTION()
	void SetPlayerHealth(const float NewHealth, const bool bDamaged = false);

	UFUNCTION()
	void StartHealthRegeneration();

	UFUNCTION()
	void StopHealthRegeneration();

	UFUNCTION()
	void UpdateHealthRegen();

	UFUNCTION()
	void OnRep_CurrentHealth();

	UFUNCTION()
	void Death();

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticastDeath();

	UFUNCTION()
	void TestVisionEntity(AActor* Entity) const;
	
	UFUNCTION()
	void TestVision();

	UFUNCTION()
	void OnVisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnVisionBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);

	UFUNCTION()
	void TestInteractables();
	
		//...

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnActionStateChanged(UPARAM() EActionState PreviousState, UPARAM() EActionState CurrentState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnCameraSettingsUpdated(UPARAM() FCameraSettings NewCameraSettings);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnShoulderUpdated(UPARAM() EShoulder NewShoulder, UPARAM() FShoulderSettings NewShoulderSettings);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnHealthFeedback(UPARAM() float NewHealth, UPARAM() float NewMaxHealth, UPARAM() float HealthPercent);

	//
	// Properties
	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* NameplateComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* VisionBoxComponent;

	UPROPERTY()
	ABaseGameMode* AuthGamemode;

	UPROPERTY()
	ABasePlayerController* CharacterPlayerController;

	UPROPERTY(EditDefaultsOnly, Category = "Display")
	TSubclassOf<UPlayerNameplate> NameplateClass;

	UPROPERTY()
	UPlayerNameplate* PlayerNameplate;

	UPROPERTY(ReplicatedUsing = OnRep_RepActionState)
	EActionState RepActionState;

	UPROPERTY()
	EActionState CurrentActionState;

	UPROPERTY()
	EActionState PreviousActionState;

	UPROPERTY()
	bool bIsSpectated;

	UPROPERTY(Replicated)
	FRotator SpectatingRotation;

	UPROPERTY()
	FTimerHandle SpectatingUpdateTimer;

	UPROPERTY(ReplicatedUsing = OnRep_RepEquipment)
	EEquipment RepEquipment;

	UPROPERTY()
	EEquipment CurrentEquipment;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponPrimary)
	ABaseWeapon* WeaponPrimary;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponSecondary)
	ABaseWeapon* WeaponSecondary;

	UPROPERTY()
	EEquipment PreviousEquipment;

	UPROPERTY(Replicated)
	float MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth)
	float CurrentHealth;

	UPROPERTY()
	AActor* CurrentInstigator;

	UPROPERTY()
	AActor* CurrentAssistInstigator;

	UPROPERTY()
	float RegenOffset;

	UPROPERTY()
	int32 CurrentRegenTick;

	UPROPERTY()
	FTimerHandle RegenerationStartTimer;

	UPROPERTY()
	FTimerHandle RegenerationUpdateTimer;

	UPROPERTY()
	bool bRegenerating;
	
	UPROPERTY(ReplicatedUsing = OnRep_Shoulder)
	EShoulder RepShoulder;

	UPROPERTY()
	EShoulder CurrentShoulder;

	UPROPERTY()
	FShoulderSettings ShoulderSettings;

	UPROPERTY()
	TArray<AActor*> VisionEntities;

	UPROPERTY()
	FTimerHandle VisionCheckTimer;

	UPROPERTY()
	bool bIsSpotted;

	UPROPERTY()
	TArray<ABaseInteractable*> Interactables;

	UPROPERTY()
	ABaseInteractable* CurrentInteractable;

	UPROPERTY()
	FTimerHandle InteractionCheckTimer;

		//...

	//
	// Interfaces
	//

	virtual ETeam GetTeam() override;
	virtual FText GetMagnaPlayerName() override;
	virtual void Damage(AActor* DamageInstigator, FDamageData Damage) override;
	virtual float GetMaxHealth() override { return MaxHealth; }
	virtual float GetCurrentHealth() override { return CurrentHealth; }
	virtual void SetEntitySpotted(const bool bSpotted, const bool bImmediate) override;
	virtual void AddInteractable(ABaseInteractable* InInteractable) override;
	virtual void RemoveInteractable(ABaseInteractable* InInteractable) override;
	virtual bool IsPlayer() override;
	virtual bool IsLocalPlayer() override;
	virtual void TestEntityInteractables() override;
	
	
		//...

	void InputMoveForward(float AxisValue);
	void InputMoveRight(float AxisValue);
	void InputLookUp(float AxisValue);
	void InputLookRight(float AxisValue);
	void InputAimPressed();
	void InputAimReleased();
	void InputEquipPrimary();
	void InputEquipSecondary();
	void InputSprintPressed();
	void InputSprintReleased();
	void InputSwapShoulder();
	void InputInteractPressed();
	
};


