// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "TimerDisplay.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UTimerDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Seconds;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Minutes;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Hours;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UHorizontalBox* HB_Hours;

public:
	UFUNCTION()
	void SetTime(const int32 Time);
	
};
