// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;  //TODO should tick?

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	
	if (!ensure(Barrel)) { return;  }
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//SuggestProjectileVelocity

	/// parameters for  enable trace debug line  for debug 
	/*bool okAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::TraceFullPath,    
		FCollisionResponseParams::DefaultResponseParam, 
		TArray<AActor*>(), 
		true);*/

	bool okAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace ); // DoNotTrace has to be here for the function to return true every frame

	if (okAimSolution) {
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("aiming  at : %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
		
		//MoveBarrel();
	}
	else {
		auto time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("55no aim solve found %f"), time);
		
	}

	
}

void UTankAimingComponent::Initialise(UTankBarrel * BarreltoSet, UTankTurret * TurrettoSet)
{
		Barrel = BarreltoSet;
		Turret = TurrettoSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 
	Turret->Rotate(DeltaRotator.Yaw);
}





