// Created and developed by Marco Silva


#include "ScoreDisplay.h"


void UScoreDisplay::NativePreConstruct()
{
	Background->SetBrushColor(BackgroundColor);
}


void UScoreDisplay::SetScore(const int32 NewScore)
{
	T_Score->SetText(FText::AsNumber(NewScore));
}

void UScoreDisplay::SetBackgroundColor(const FLinearColor NewColor)
{
	BackgroundColor = NewColor;
	Background->SetBrushColor(NewColor);
}
