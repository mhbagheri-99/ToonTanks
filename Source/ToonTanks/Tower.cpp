// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	// Sets the timer (to handle towers fire rate)
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange()) 
	{
		// Starts aiming at the Tank if it is in range
		RotateTurret(Tank->GetActorLocation());
	}
		
}

// Checks if the Tank is in Range of Fire
bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= FireRange) 
		{
			return true;
		}
	}
	return false;
}

void ATower::CheckFireCondition()
{
	// if the Tank is Alive and in Fire Range it Fires
	if (Tank && Tank->bAlive && InFireRange()) 
	{
		Fire();
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();

	Destroy();
}