// Created and developed by Marco Silva


#include "PlayerNameplate.h"

#include "ProjectMagna/Statics/MagnaStatics.h"


void UPlayerNameplate::NativeConstruct()
{
	Super::NativeConstruct();
	
}


void UPlayerNameplate::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	const float InterpSpeed = bSpotted ? InterpSpeedSpotted : InterpSpeedNotSpotted;
	const float NewOpacity = FMath::FInterpConstantTo(Background->GetRenderOpacity(), bSpotted ? 1.0f : 0.0f, InDeltaTime, InterpSpeed);

	this->Background->SetRenderOpacity(NewOpacity);
}


void UPlayerNameplate::SetPlayerName(const FText Name)
{
	T_PlayerName->SetText(Name);
}

void UPlayerNameplate::SetNameplateColor(const FColor Color)
{
	Background->SetContentColorAndOpacity(Color);
}

void UPlayerNameplate::SetPlayerSpotted(const bool bNewValue, const bool bImmediate)
{
	bSpotted = bNewValue;

	if (bImmediate)
	{
		this->Background->SetRenderOpacity(bSpotted ? 1.0f : 0.0f);
	}
}

