// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Setting Up and Attaching the Necessary Meshes and Components
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1000.f;
	ProjectileMovementComponent->MaxSpeed = 1500.f;

	//Sets a smoke trail VFX
	TrailParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle Component"));
	TrailParticleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	// Binding our OnHit function to OnComponentHit of OnComponentHit (it will be called upon that)
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	// Launch SFX
	if (LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Function to handle all necessary things after the projectile hits the target
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner();

	if (ProjectileOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* ProjectileOwnerInstigator = ProjectileOwner->GetInstigatorController();
	//Returns the UClass 
	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
	{
		// Calls the DamageTaken function
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwnerInstigator, this, DamageTypeClass);
		
		//UE_LOG(LogTemp, Warning, TEXT("%f damage taken."), Damage);

		//Small Explosion VFX
		if (HitParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
		}
		//Small Explosion SFX
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
		//Explosion Camera Shake (Less intense compared to tanks and towers explosion shake)
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}
	// Destroys the projectile
	Destroy();
}

