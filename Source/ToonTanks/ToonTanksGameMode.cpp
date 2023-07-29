// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

// Handles what to do when a pawn dies
void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (Tank->GetTankPlayerController())
		{
			//Disables the player inputs
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		// If it's false it is a lose situation
		GameOver(false);
	}

	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		if (TargetTowers == 0)
		{
			// If it's true it is a win situation
			GameOver(true);
		}
	}

}

void AToonTanksGameMode::BeginPlay() 
{
	Super::BeginPlay();

	HandleGameStart();

	// Counts the Towers (Enemies) in the Game
	TargetTowers = GetTargetTowersCount();

	//ToonTanksPlayerController->SetPlayerEnabledState(true);
}

void AToonTanksGameMode::HandleGameStart()
{
	// Gives Tank Control to the player
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	// HUD for starting the game
	StartGame();

	if (ToonTanksPlayerController)
	{
		// Temporarily Disables the Player Input for the start counter to pass
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		// Enables the Player Input after the timer finishes
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTanksPlayerController, 
			&AToonTanksPlayerController::SetPlayerEnabledState, 
			true
		);
		// Sets the StartDelay Timer with the defined PlayerEnableTimerHandle and PlayerEnableTimerDelegate
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
		);
	}
}

// Counts the number of Towers
int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}