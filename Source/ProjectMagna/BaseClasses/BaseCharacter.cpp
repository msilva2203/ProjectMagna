// Created and developed by Marco Silva


#include "BaseCharacter.h"

#include "BaseGameMode.h"
#include "BasePlayerController.h"
#include "BaseWeapon.h"
#include "BaseInteractable.h"
#include "ProjectMagna/Widgets/PlayerNameplate.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Evaluation/PreAnimatedState/MovieScenePreAnimatedStateTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "ProjectMagna/Statics/MagnaAssetManager.h"
#include "ProjectMagna/Statics/MagnaStatics.h"


// Default Values
#define SPEED_DEFAULT				220.0f
#define SPEED_SPRINTING				310.0f
#define SPEED_AIMING				160.0f

#define CAMERA_HEIGHT_DEFAULT		75.0f
#define CAMERA_HEIGHT_SPRINTING		45.0f

#define SHOULDER_OFFSET_DEFAULT		45.0f

#define SPECTATING_UPDATE_RATE		0.07f
#define SPECTATING_ROTATION_SPEED	10.0f

#define REGEN_START_TIME			5.0f
#define REGEN_UPDATE_TIME			3.0f
#define REGEN_UPDATE_TICKS			12

#define VISION_RATE					0.30f

#define INTERACTION_CHECK_TIME		0.15f


// Sets replicated variables
void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ABaseCharacter, ActionState);
	DOREPLIFETIME(ABaseCharacter, CurrentEquipment);
	DOREPLIFETIME(ABaseCharacter, WeaponPrimary);
	DOREPLIFETIME(ABaseCharacter, WeaponSecondary);
	DOREPLIFETIME(ABaseCharacter, MaxHealth);
	DOREPLIFETIME(ABaseCharacter, CurrentHealth);
	DOREPLIFETIME(ABaseCharacter, RepShoulder);
	DOREPLIFETIME(ABaseCharacter, SpectatingRotation);
}

// Sets default values
ABaseCharacter::ABaseCharacter() :
	NameplateClass(UPlayerNameplate::StaticClass()),
	ActionState(EActionState::None),
	PreviousActionState(EActionState::None),
	bIsSpectated(false),
	PreviousEquipment(EEquipment::None),
	bRegenerating(false),
	bIsSpotted(false)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	GetCapsuleComponent()->SetHiddenInGame(false);
	GetCapsuleComponent()->SetVisibility(true);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	NameplateComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Nameplate"));
	VisionBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Vision Box"));
	
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetupAttachment(SpringArmComponent);
	NameplateComponent->SetupAttachment(GetMesh());
	VisionBoxComponent->SetupAttachment(CameraComponent);
	
	SpringArmComponent->bUsePawnControlRotation = true;

	NameplateComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NameplateComponent->SetRelativeLocation(FVector(0.0, 0.0, 120.0));
	NameplateComponent->SetDrawAtDesiredSize(true);

	VisionBoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	VisionBoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	VisionBoxComponent->SetGenerateOverlapEvents(true);
	VisionBoxComponent->SetActive(false);
	
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetNetMode() < NM_Client)
	{
		ServerSetActionState(EActionState::Default, true);
		ServerPickupWeapon(EWeapon::FS92);
		ServerPickupWeapon(EWeapon::AK47);

		AuthGamemode = Cast<ABaseGameMode>(GetWorld()->GetAuthGameMode());

		GetWorldTimerManager().SetTimer(SpectatingUpdateTimer, this, &ABaseCharacter::OnSpectatingUpdate, SPECTATING_UPDATE_RATE, true);
		
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsLocallyControlled())
	{
		// Local tick here...

		
	}
	else
	{
		// Not local tick here...
		
		if (bIsSpectated)
		{
			const FRotator CurrentRotation = SpringArmComponent->GetComponentRotation();
			const FRotator NewRotation = FMath::RInterpTo(CurrentRotation, SpectatingRotation, DeltaTime, SPECTATING_ROTATION_SPEED);
			SpringArmComponent->SetWorldRotation(NewRotation);
		}
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Axis Mappings
	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseCharacter::InputMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseCharacter::InputMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseCharacter::InputLookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ABaseCharacter::InputLookRight);
	
	// Action Mappings
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ABaseCharacter::InputAimPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ABaseCharacter::InputAimReleased);
	PlayerInputComponent->BindAction("EquipPrimary", IE_Pressed, this, &ABaseCharacter::InputEquipPrimary);
	PlayerInputComponent->BindAction("EquipSecondary", IE_Pressed, this, &ABaseCharacter::InputEquipSecondary);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharacter::InputSprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharacter::InputSprintReleased);
	PlayerInputComponent->BindAction("SwapShoulder", IE_Pressed, this, &ABaseCharacter::InputSwapShoulder);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABaseCharacter::InputInteractPressed);
	
}

void ABaseCharacter::OnRep_PlayerState()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Purple, TEXT("Character is ready on this client"));
	SetupCharacter();
}


//
// Methods
//

void ABaseCharacter::SetupCharacter()
{
	ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
	
	if (IsLocallyControlled())
	{
		// Setup on local client
		PlayerController->SetPlayerGameState(EPlayerGameState::Playing);

		VisionBoxComponent->SetActive(true, true);
		VisionBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseCharacter::OnVisionBoxBeginOverlap);
		VisionBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ABaseCharacter::OnVisionBoxEndOverlap);
		GetWorldTimerManager().SetTimer(VisionCheckTimer, this, &ABaseCharacter::TestVision, VISION_RATE, true);
		GetWorldTimerManager().SetTimer(InteractionCheckTimer, this, &ABaseCharacter::TestInteractables, INTERACTION_CHECK_TIME, true);
	}
	else
	{
		// Setup on other clients
		PlayerNameplate = CreateWidget<UPlayerNameplate>(GetWorld()->GetFirstPlayerController(), NameplateClass);
		PlayerNameplate->SetPlayerName(PlayerController->GetMagnaPlayerName());
		PlayerNameplate->SetNameplateColor(UMagnaStatics::GetEntityColor(PlayerController->GetTeam(), this->GetTeam(), PlayerController->Gamemode));
		PlayerNameplate->SetPlayerSpotted(GetTeam() == PlayerController->GetTeam() ? true : bIsSpotted, true);
		
		NameplateComponent->SetWidget(PlayerNameplate);
		
		if (GetTeam() == PlayerController->GetTeam())
		{
			PlayerController->AddTeammate(this);
			
		}
		
		SpringArmComponent->bUsePawnControlRotation = false;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritYaw = false;
		
		VisionBoxComponent->SetActive(false);
		
	}
}


void ABaseCharacter::ServerSetActionState_Implementation(const EActionState NewState, const bool bForceUpdate)
{
	if (NewState != ActionState || bForceUpdate)
	{
		ActionState = NewState;
		OnRep_ActionState();
	}
}

void ABaseCharacter::SetActionState(const EActionState State, const bool bNewValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, FColor::Red, TEXT("Player Action State changed!"));
	
	switch (State)
	{
	case EActionState::None:
		break;
	case EActionState::Default:
		SetDefaultState(bNewValue);
		break;
	case EActionState::Sprinting:
		SetSprintingState(bNewValue);
		break;
	case EActionState::Aiming:
		SetAimingState(bNewValue);
		break;
	default:
		break;
	}
}

void ABaseCharacter::SetDefaultState(const bool bNewValue)
{
	if (bNewValue)
	{
		GetCharacterMovement()->MaxWalkSpeed = SPEED_DEFAULT;
		this->bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		FCameraSettings CameraSettings;
		CameraSettings.CameraLength = 230.0;
		CameraSettings.CameraHeight = CAMERA_HEIGHT_DEFAULT;
		CameraSettings.TransitionTime = 0.2;
		OnCameraSettingsUpdated(CameraSettings);

		ShoulderSettings.ShoulderOffset = SHOULDER_OFFSET_DEFAULT;
		ShoulderSettings.TransitionTime = 0.4;
		SetShoulder(EShoulder::Right);
		
	}
	else
	{
		
	}
}

void ABaseCharacter::SetSprintingState(const bool bNewValue)
{
	if (bNewValue)
	{
		GetCharacterMovement()->MaxWalkSpeed = SPEED_SPRINTING;
		this->bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;

		FCameraSettings CameraSettings;
		CameraSettings.CameraLength = 130.0;
		CameraSettings.CameraHeight = CAMERA_HEIGHT_SPRINTING;
		CameraSettings.TransitionTime = 1.0;
		OnCameraSettingsUpdated(CameraSettings);

		ShoulderSettings.ShoulderOffset = 0.0;
		ShoulderSettings.TransitionTime = 1.0;
		SetShoulder(EShoulder::Center);
		
	}
	else
	{
		
	}
}

void ABaseCharacter::SetAimingState(const bool bNewValue)
{
	if (bNewValue)
	{
		GetCharacterMovement()->MaxWalkSpeed = SPEED_AIMING;
		this->bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;

		FCameraSettings CameraSettings;
		CameraSettings.CameraLength = 60.0;
		CameraSettings.CameraHeight = CAMERA_HEIGHT_DEFAULT;
		CameraSettings.TransitionTime = 0.2;
		OnCameraSettingsUpdated(CameraSettings);

		ShoulderSettings.ShoulderOffset = SHOULDER_OFFSET_DEFAULT;
		ShoulderSettings.TransitionTime = 0.4;
		SetShoulder(EShoulder::Right);
	}
	else
	{
		
	}
}


void ABaseCharacter::OnRep_ActionState()
{
	SetActionState(PreviousActionState, false);
	SetActionState(ActionState, true);
	OnActionStateChanged(PreviousActionState, ActionState);
	PreviousActionState = ActionState;
	
}

void ABaseCharacter::SetSpectating(const bool bNewValue)
{
	bIsSpectated = bNewValue;

	if (bIsSpectated)
	{
		SpringArmComponent->SetWorldRotation(SpectatingRotation);
		
		FViewTargetTransitionParams TransitionParams;
		TransitionParams.BlendTime = 0.0;
		GetWorld()->GetFirstPlayerController()->SetViewTarget(this, TransitionParams);
	}
	
}

// Will only be called on the server
void ABaseCharacter::OnSpectatingUpdate()
{
	SpectatingRotation = GetBaseAimRotation();
}


void ABaseCharacter::ServerPickupWeapon_Implementation(const EWeapon Weapon)
{
	const FTransform SpawnTransform = GetActorTransform();
	ABaseWeapon* NewWeapon = GetWorld()->SpawnActorDeferred<ABaseWeapon>(ABaseWeapon::StaticClass(), SpawnTransform);
	
	// Weapon Setup here
	NewWeapon->SetOwner(GetController());
	NewWeapon->Player = Cast<ABasePlayerController>(GetController());
	NewWeapon->Character = this;
	NewWeapon->GameWeaponSettings = AuthGamemode->MatchSettings.WeaponSettings;

	NewWeapon->FinishSpawning(SpawnTransform);
	
	switch (NewWeapon->GetEquipmentSlot())
	{
	case EEquipment::None:
		break;
	case EEquipment::Primary:
		WeaponPrimary = NewWeapon;
		break;
	case EEquipment::Secondary:
		WeaponSecondary = NewWeapon;
		break;
	default:
		break;
	}
}


void ABaseCharacter::OnRep_CurrentEquipment()
{
	EquipWeapon(CurrentEquipment);
}

void ABaseCharacter::OnRep_WeaponPrimary()
{
	EquipWeapon(EEquipment::Primary);
}

void ABaseCharacter::OnRep_WeaponSecondary()
{
	EquipWeapon(EEquipment::Secondary);
}

void ABaseCharacter::ServerEquipWeapon_Implementation(const EEquipment NewEquipment)
{
	EquipWeapon(NewEquipment);
}

void ABaseCharacter::EquipWeapon(const EEquipment NewEquipment)
{
	if (PreviousEquipment != NewEquipment)
	{
		CurrentEquipment = NewEquipment;
		if (IsValid(GetPlayerWeapon(PreviousEquipment)))
			GetPlayerWeapon(PreviousEquipment)->UnEquipWeapon(IsLocallyControlled());
		GetPlayerWeapon(CurrentEquipment)->EquipWeapon(IsLocallyControlled());
		PreviousEquipment = CurrentEquipment;
	}
}

ABaseWeapon* ABaseCharacter::GetPlayerWeapon(const EEquipment Equipment)
{
	switch (Equipment)
	{
		case EEquipment::None:
			return nullptr;
		case EEquipment::Primary:
			return WeaponPrimary;
		case EEquipment::Secondary:
			return WeaponSecondary;
		default:
			return nullptr;
	}
}

void ABaseCharacter::ServerSetShoulder_Implementation(const EShoulder NewShoulder)
{
	RepShoulder = NewShoulder;
	SetShoulder(NewShoulder);
}

void ABaseCharacter::OnRep_Shoulder()
{
	SetShoulder(RepShoulder);
}

void ABaseCharacter::SetShoulder(const EShoulder NewShoulder, const bool bReplicate)
{
	CurrentShoulder = NewShoulder;

	// Shoulder Functionality here...
	OnShoulderUpdated(CurrentShoulder, ShoulderSettings);

	if (bReplicate)
	{
		ServerSetShoulder(CurrentShoulder);
	}
	
}

void ABaseCharacter::SetPlayerHealth(const float NewHealth, const bool bDamaged)
{
	CurrentHealth = NewHealth;
	
	if (GetNetMode() == NM_ListenServer)
		OnRep_CurrentHealth();
	
	if (bDamaged)
		StartHealthRegeneration();

	if (CurrentHealth <= 0.0f)
	{
		// Player death here
		Death();
		NetMulticastDeath();
	}
}

void ABaseCharacter::StartHealthRegeneration()
{
	if (bRegenerating)
	{
		if (GetWorldTimerManager().IsTimerActive(RegenerationStartTimer))
		{
			GetWorldTimerManager().ClearTimer(RegenerationStartTimer);
		}
		else if (GetWorldTimerManager().IsTimerActive(RegenerationUpdateTimer))
		{
			GetWorldTimerManager().ClearTimer(RegenerationUpdateTimer);
		}
	}

	this->RegenOffset = (MaxHealth - CurrentHealth) / REGEN_UPDATE_TICKS;
	this->CurrentRegenTick = 0;
	bRegenerating = true;
	
	GetWorldTimerManager().SetTimer(RegenerationStartTimer, this, &ABaseCharacter::UpdateHealthRegen, REGEN_START_TIME, false);
}

void ABaseCharacter::UpdateHealthRegen()
{
	if (GetWorldTimerManager().IsTimerActive(RegenerationUpdateTimer))
	{
		this->CurrentRegenTick++;
		if (CurrentRegenTick == REGEN_UPDATE_TICKS)
		{
			SetPlayerHealth(MaxHealth, false);
			GetWorldTimerManager().ClearTimer(RegenerationUpdateTimer);
			bRegenerating = false;
		}
		else
		{
			SetPlayerHealth(CurrentHealth + RegenOffset, false);
		}
	}
	else
	{
		GetWorldTimerManager().SetTimer(RegenerationUpdateTimer, this, &ABaseCharacter::UpdateHealthRegen, REGEN_UPDATE_TIME / REGEN_UPDATE_TICKS, true);
	}
}

void ABaseCharacter::OnRep_CurrentHealth()
{
	OnHealthFeedback(CurrentHealth, MaxHealth, CurrentHealth / MaxHealth);
	
}

void ABaseCharacter::Death()
{
	OnHealthFeedback(MaxHealth, MaxHealth, 1.0);

	if (GetWorld()->GetNetMode() < NM_Client)
	{
		CharacterPlayerController->UnPossess();
		CharacterPlayerController->OnPlayerDeath(CurrentInstigator);
	}

	if (!IsLocallyControlled())
	{
		ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
		if (PlayerController)
		{
			if (GetTeam() == PlayerController->GetTeam())
				PlayerController->RemoveTeammate(this);
			
		}
	}

	GetCharacterMovement()->StopMovementImmediately();
	GetMesh()->SetSimulatePhysics(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	
}

void ABaseCharacter::NetMulticastDeath_Implementation()
{
	Death();
}

void ABaseCharacter::TestVisionEntity(AActor* Entity) const
{
	IInteractionInterface* Interface = Cast<IInteractionInterface>(Entity);
	
	if (Interface)
	{
		FVector StartLocation = CameraComponent->GetComponentLocation();
		FVector EndLocation = Entity->GetActorLocation();
	
		FCollisionQueryParams TraceParams;
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.AddIgnoredActor(this);

		FHitResult Result(ForceInit);

		GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECC_Camera, TraceParams);

		if (Result.bBlockingHit)
		{
			if (Entity == Result.GetActor())
			{
				Interface->SetEntitySpotted(true, false);
			}
			else
			{
				Interface->SetEntitySpotted(false, false);
			}
		}
		else
		{
			Interface->SetEntitySpotted(false, false);
		}
	}
}

void ABaseCharacter::TestVision()
{
	for (const auto Entity : VisionEntities)
	{
		TestVisionEntity(Entity);
	}
}


void ABaseCharacter::OnVisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0, TEAM_COLOR_HEROES, TEXT("New actor in vision"));
	
	if (!VisionEntities.Contains(OtherActor))
	{
		IMagnaInterface* Interface = Cast<IMagnaInterface>(OtherActor);
		if (Interface)
		{
			if (Interface->GetTeam() != GetTeam())
			{
				VisionEntities.Add(OtherActor);
				TestVisionEntity(OtherActor);
			}
		}
	}
	
}

void ABaseCharacter::OnVisionBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (VisionEntities.Contains(OtherActor))
	{
		VisionEntities.Remove(OtherActor);

		IInteractionInterface* Interface = Cast<IInteractionInterface>(OtherActor);
		if (Interface)
		{
			Interface->SetEntitySpotted(false, false);
		}
	}
	
}

void ABaseCharacter::TestInteractables()
{
	float Distance = 1000.0f;
	ABaseInteractable* NewInteractable = nullptr;

	if (Interactables.IsEmpty())
	{
		CurrentInteractable = NewInteractable;
		return;
	}

	for (auto In : Interactables)
	{
		if (In->IsActive())
		{
			FVector StartLocation = GetActorLocation();
			FVector EndLocation = In->GetActorLocation();

			//FHitResult Result(ForceInit);
			//GetWorld()->LineTraceSingleByChannel(Result, StartLocation, EndLocation, ECC_Visibility);
			//
			//if (Result.bBlockingHit)
			//{
			//	if (Result.GetActor() == In)
			//	{
			//		float NewDistance = FVector::Distance(StartLocation, EndLocation);
			//		if (NewDistance <= Distance)
			//		{
			//			CurrentInteractable = In;
			//			Distance = NewDistance;
			//		}
			//	}
			//}

			float NewDistance = FVector::Distance(StartLocation, EndLocation);
			if (NewDistance <= Distance)
			{
				NewInteractable = In;
				Distance = NewDistance;
			}
		}
	}

	CurrentInteractable = NewInteractable;
}



//
// Interfaces
//

ETeam ABaseCharacter::GetTeam()
{
	IMagnaInterface* Interface = Cast<IMagnaInterface>(GetPlayerState());
	
	if (Interface)
	{
		return Interface->GetTeam();
	}
	
	return ETeam::None;
}

FText ABaseCharacter::GetMagnaPlayerName()
{
	IMagnaInterface* Interface = Cast<IMagnaInterface>(GetPlayerState());

	if (Interface)
	{
		return Interface->GetMagnaPlayerName();
	}
	
	return FText::FromString("Magna Player");
}

// Will only be called on the server
void ABaseCharacter::Damage(AActor* DamageInstigator, FDamageData Damage)
{
	IMagnaInterface* Interface = Cast<IMagnaInterface>(DamageInstigator);
	if (Interface)
	{
		if (Interface->GetTeam() != GetTeam() || AuthGamemode->IsFriendlyFireActive())
		{
			float Health = CurrentHealth - Damage.Damage;
			Health = FMath::Clamp(Health, 0.0f, MaxHealth);

			if (IsValid(CurrentInstigator))
			{
				IMagnaInterface* InstigatorInterface = Cast<IMagnaInterface>(CurrentInstigator);
				if (InstigatorInterface)
				{
					if (InstigatorInterface->GetTeam() != GetTeam() && Interface->GetTeam() == InstigatorInterface->GetTeam())
						CurrentAssistInstigator = CurrentInstigator;
				}
				
			}
			CurrentInstigator = DamageInstigator;

			SetPlayerHealth(Health, true);
		}
	}
	
}

void ABaseCharacter::SetEntitySpotted(const bool bSpotted, const bool bImmediate)
{
	this->bIsSpotted = bSpotted;
	
	if (IsValid(PlayerNameplate))
	{
		PlayerNameplate->SetPlayerSpotted(bSpotted, bImmediate);
	}
}

void ABaseCharacter::AddInteractable(ABaseInteractable* InInteractable)
{
	if (!Interactables.Contains(InInteractable))
	{
		Interactables.Add(InInteractable);
		TestInteractables();
	}
}

void ABaseCharacter::RemoveInteractable(ABaseInteractable* InInteractable)
{
	if (Interactables.Contains(InInteractable))
	{
		Interactables.Remove(InInteractable);
		if (InInteractable == CurrentInteractable)
			TestInteractables();
	}
}

bool ABaseCharacter::IsPlayer()
{
	return true;
}

bool ABaseCharacter::IsLocalPlayer()
{
	return IsLocallyControlled();
}

void ABaseCharacter::TestEntityInteractables()
{
	TestInteractables();
}


//
// Inputs
//


void ABaseCharacter::InputMoveForward(float AxisValue)
{
	FRotator ViewRotation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraRotation();
	ViewRotation.Pitch = 0.0;
	ViewRotation.Roll = 0.0;
	FVector Direction = UKismetMathLibrary::GetForwardVector(ViewRotation);

	AddMovementInput(Direction, AxisValue);
}

void ABaseCharacter::InputMoveRight(float AxisValue)
{
	FRotator ViewRotation = UGameplayStatics::GetPlayerCameraManager(this, 0)->GetCameraRotation();
	ViewRotation.Pitch = 0.0;
	ViewRotation.Roll = 0.0;
	FVector Direction = UKismetMathLibrary::GetRightVector(ViewRotation);

	AddMovementInput(Direction, AxisValue);
}

void ABaseCharacter::InputLookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ABaseCharacter::InputLookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ABaseCharacter::InputAimPressed()
{
	ServerSetActionState(EActionState::Aiming);
}

void ABaseCharacter::InputAimReleased()
{
	ServerSetActionState(EActionState::Default);
}

void ABaseCharacter::InputEquipPrimary()
{
	ServerEquipWeapon(EEquipment::Primary);

	FDamageData Damage;
	Damage.Damage = 10.0;
	Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController())->ServerDamageEntity(this, Damage);
}

void ABaseCharacter::InputEquipSecondary()
{
	ServerEquipWeapon(EEquipment::Secondary);
}

void ABaseCharacter::InputSprintPressed()
{
	if (ActionState != EActionState::Aiming)
	{
		ServerSetActionState(EActionState::Sprinting);
	}
}

void ABaseCharacter::InputSprintReleased()
{
	if (ActionState == EActionState::Sprinting)
	{
		ServerSetActionState(EActionState::Default);
	}
}

void ABaseCharacter::InputSwapShoulder()
{
	if (ActionState == EActionState::Aiming)
	{
		switch (CurrentShoulder)
		{
		case EShoulder::Center:
			break;
		case EShoulder::Right:
			SetShoulder(EShoulder::Left, true);
			break;
		case EShoulder::Left:
			SetShoulder(EShoulder::Right, true);
			break;
		default:
			break;
		}
	}
}

void ABaseCharacter::InputInteractPressed()
{
	if (IsValid(CurrentInteractable))
	{
		if (CurrentInteractable->IsActive())
		{
			ABasePlayerController* PlayerController = Cast<ABasePlayerController>(GetWorld()->GetFirstPlayerController());
			PlayerController->ServerInteract(CurrentInteractable);

			RemoveInteractable(CurrentInteractable);
		}
	}
}
