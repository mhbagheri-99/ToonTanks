// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	//Made protected Cause it was needed in the Tank(child) to help with the camera system
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		UStaticMeshComponent* BaseMesh;

	void RotateTurret(FVector LookAtTarget);

	void Fire();

	UPROPERTY(EditAnywhere, Category = "Combat")
		class UParticleSystem* ExplosionParticle;

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivateAccess = "true"), BlueprintReadOnly)
		USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		class USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class UCameraShakeBase> ExplosionCameraShakeClass;

};
