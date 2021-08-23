// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}


void ATank::AimAt(FVector HitLocation)
{

	if (!ensure(TankAimingComponent)) { return; }
	//UE_LOG(LogTemp, Warning, TEXT("aim solve found 99"));
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed); //, LaunchSpeed	

}

void ATank::Fire()
{


	if (!ensure(Barrel)) { return;  }


	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeinSeconds;

	if (isReloaded) 
	{

		FVector location = Barrel->GetSocketLocation(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));


		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

	}


}


