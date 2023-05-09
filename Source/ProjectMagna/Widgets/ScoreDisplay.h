// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "ScoreDisplay.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMAGNA_API UScoreDisplay : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativePreConstruct() override;

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_Score;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* Background;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor BackgroundColor;

public:
	UFUNCTION()
	void SetScore(const int32 NewScore);

	UFUNCTION()
	void SetBackgroundColor(const FLinearColor NewColor);
};
