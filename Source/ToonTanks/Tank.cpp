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
	DeltaLocation.X = Value * Speed * DeltaSeconds;

	AddActorLocalOffset(DeltaLocation);
}