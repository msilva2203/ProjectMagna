// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "ScoreDisplay.h"
#include "TimerDisplay.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD_TDM.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UGameHUD_TDM : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTimerDisplay* GameTimer;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UScoreDisplay* Score_PlayerTeam;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UScoreDisplay* Score_EnemyTeam;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UScoreDisplay* Score_ObjectiveGoal;

public:
	UFUNCTION()
	void SetTimeRemaining(const int32 Time);

	UFUNCTION()
	void SetPlayerTeamScore(const int32 NewScore);

	UFUNCTION()
	void SetEnemyTeamScore(const int32 NewScore);

	UFUNCTION()
	void SetObjectiveGoal(const int32 NewScore);
	
};
