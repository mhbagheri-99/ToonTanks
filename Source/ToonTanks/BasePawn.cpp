// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
//#include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "Camera/CameraShakeBase.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting Up and Attaching the Necessary Meshes and Components for our Pawns
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

//Function that handles rotating the turret mesh to the mouse pointer in game
//in other words, aiming system for the turrets
void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	//Using Interpolate rotator to rotate the turret smoothly
	TurretMesh->SetWorldRotation (
		FMath::RInterpTo (
			TurretMesh->GetComponentRotation(),
			LookAtRotation,
			UGameplayStatics::GetWorldDeltaSeconds(this),
			20.f
		)
	);
}

// Function to handle firing projectiles from the spawn point of the turret
void ABasePawn::Fire()
{
	/*
	DrawDebugSphere
	(
		GetWorld(),
		ProjectileSpawnPoint->GetComponentLocation(),
		10.f,
		12.f,
		FColor::Red,
		false,
		3.f
	);
	*/

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation()
	);
	// It is set here to avoid friendly fire and self-harming projectiles
	Projectile->SetOwner(this);
}

//Cleaning up the scenery after the pawn is destroyed
void ABasePawn::HandleDestruction()
{
	//Explosion VFX
	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionParticle, GetActorLocation(), GetActorRotation());
	}
	//Explosion SFX
	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}
	//Explosion Camera Shake (More intense compared to projectile explosion shake)
	if (ExplosionCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(ExplosionCameraShakeClass);
	}
}