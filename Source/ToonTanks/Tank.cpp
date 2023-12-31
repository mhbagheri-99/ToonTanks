// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() 
{
	//Creating and Connecting the Spring Arm Component to our Base Mesh
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BaseMesh);
	//Creating and Connecting the Camera to the Spring Arm Component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

//Needed to Bind the Axis for Player Movement Control
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Binding the MoveForward Axis to our Player Input Component
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	//Binding the Turn Axis to our Player Input Component
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	//Binding the Fire Action to our Player Input Component
	//It happens as soon as it is pressed
	//Should be modified for guns with a higher rate of fire (rapid firing while it is pressed)
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController)
	{
		FHitResult HitResult;
		// Gets the location of the mouse cursor (aim)
		TankPlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult
		);

		RotateTurret(HitResult.ImpactPoint);
	}

}

//Function that Handles the Tank's Movement
void ATank::Move(float Value) 
{
	//UE_LOG(LogTemp, Display, TEXT("The Value is: %f"), Value);
	
	//Setting Up and Controling the X-Axis Movement
	FVector DeltaLocation = FVector::ZeroVector;
	//Using Delta Seconds to Make the Movement Smoother (Handles the FPS Change Problem)
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	//Value(W) = 1 & Value(S) = -1
	DeltaLocation.X = Value * MoveSpeed * DeltaSeconds;

	AddActorLocalOffset(DeltaLocation, true);
}

//Function that Handles the Tank's Turret's Rotation
//Similar to above
void ATank::Turn(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	float DeltaSeconds = UGameplayStatics::GetWorldDeltaSeconds(this);
	DeltaRotation.Yaw = Value * RotateSpeed * DeltaSeconds;
	AddActorLocalRotation(DeltaRotation);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	// Hides the tank (the player's pawn)
	SetActorHiddenInGame(true);
	// Disables the tick function to improve performance
	SetActorTickEnabled(false);
	// Declares the tank is dead
	bAlive = false;
}

APlayerController* ATank::GetTankPlayerController() const
{
	return TankPlayerController;
}