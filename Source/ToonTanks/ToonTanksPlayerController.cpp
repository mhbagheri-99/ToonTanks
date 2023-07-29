// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

// (De)Activates the player input for the pawn
void AToonTanksPlayerController::SetPlayerEnabledState(bool bPlayerEnabled)
{
	if (bPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
	bShowMouseCursor = bPlayerEnabled;
}