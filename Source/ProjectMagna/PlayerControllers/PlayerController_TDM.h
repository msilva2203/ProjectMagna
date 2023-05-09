// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ProjectMagna/BaseClasses/BasePlayerController.h"
#include "ProjectMagna/Widgets/GameHUD_TDM.h"
#include "PlayerController_TDM.generated.h"


// Forward Declarations
class AGameState_TDM;

UCLASS()
class PROJECTMAGNA_API APlayerController_TDM : public ABasePlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerController_TDM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ShowGameHUD() override;
	virtual void HideGameHUD() override;

	virtual void SetupPlayer_Implementation() override;
	virtual void StartPlayer_Implementation() override;
	
	virtual void OnPlayerKill(AActor* KilledActor) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player HUD")
	TSubclassOf<UGameHUD_TDM> HUDSubclass;
	
	UPROPERTY(BlueprintReadWrite)
	UGameHUD_TDM* GameHUD_TDM;

	UPROPERTY()
	AGameState_TDM* GameState_TDM;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateGameHUD();

	UFUNCTION()
	UGameHUD_TDM* GetGameHUD();
};
