// Created and developed by Marco Silva


#include "TimerDisplay.h"

void UTimerDisplay::SetTime(const int32 Time)
{
	int32 Hours = Time / 3600;
	T_Seconds->SetText(FText::AsNumber(Time % 60));
	T_Minutes->SetText(FText::AsNumber((Time % 3600) / 60));
	T_Hours->SetText(FText::AsNumber(Hours));

	if (Hours > 0)
	{
		HB_Hours->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HB_Hours->SetVisibility(ESlateVisibility::Collapsed);
	}
}
