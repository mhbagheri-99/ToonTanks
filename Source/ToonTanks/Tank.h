// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:

	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//To attach the Camera for a more dynamic camera movement
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* Camera;
	//Speed Modifier
	UPROPERTY(EditAnywhere, Category = "Movements")
		float MoveSpeed = 250.0;

	UPROPERTY(EditAnywhere, Category = "Movements")
		float RotateSpeed = 100.0;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* PlayerControllerRef;
};
