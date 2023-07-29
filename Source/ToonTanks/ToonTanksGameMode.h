// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	void ActorDied(AActor* DeadActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Blueprint Function to Start the Game (Used in HUD for game start up)
	UFUNCTION(BlueprintImplementableEvent)
		void StartGame();
	// Blueprint Function to End the Game (Used in HUD for game over)
	UFUNCTION(BlueprintImplementableEvent)
		void GameOver(bool bWonTheGame);

private:
	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;

	// How many seconds before the Game Starts
	float StartDelay = 3.f;
	void HandleGameStart();

	int32 TargetTowers = 0;
	int32 GetTargetTowersCount();
	
};
