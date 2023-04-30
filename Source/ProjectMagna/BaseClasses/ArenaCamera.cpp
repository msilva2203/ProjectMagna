// Created and developed by Marco Silva


#include "ArenaCamera.h"


// Sets default values
AArenaCamera::AArenaCamera()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Arena Camera"));
	CameraComponent->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void AArenaCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AArenaCamera::SpectateCamera()
{
	FViewTargetTransitionParams TransitionParams;
	TransitionParams.BlendTime = 0.0;
	
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this, TransitionParams);
	GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, TEXT("View target is now the Arena Camera"));
	
}

