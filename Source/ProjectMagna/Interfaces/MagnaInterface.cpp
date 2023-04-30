// Created and developed by Marco Silva


#include "MagnaInterface.h"


// Add default functionality here for any IMagnaInterface functions that are not pure virtual.

ETeam IMagnaInterface::GetTeam()
{
	return ETeam::None;
}

FText IMagnaInterface::GetMagnaPlayerName()
{
	return FText::FromString("Magna Player");
}
