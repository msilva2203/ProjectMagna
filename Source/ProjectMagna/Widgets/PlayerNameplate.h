// Created and developed by Marco Silva

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "PlayerNameplate.generated.h"

/**
 *
 * 
 */
UCLASS(Abstract)
class PROJECTMAGNA_API UPlayerNameplate : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	void SetPlayerName(const FText Name);
	void SetNameplateColor(const FColor Color);

	UFUNCTION()
	void SetPlayerSpotted(const bool bNewValue, const bool bImmediate = false);

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* T_PlayerName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBorder* Background;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nameplate")
	float InterpSpeedSpotted = 0.2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nameplate")
	float InterpSpeedNotSpotted = 0.4;

	UPROPERTY()
	bool bSpotted;
	
};
