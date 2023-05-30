// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"


// Forward Declarations
class ABasePlayerController;

UCLASS()
class PROJECTMAGNA_API ABaseInteractable : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);

	UFUNCTION()
	virtual void Interact(ABasePlayerController* PlayerController);

	UFUNCTION()
	bool IsActive();

	UFUNCTION()
	void SetActive(const bool bNewValue);

	UFUNCTION()
	void OnRep_Active();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY()
	AActor* CurrentActor;

	UPROPERTY(ReplicatedUsing = OnRep_Active)
	bool bActive;
};
