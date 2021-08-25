// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;  //TODO should tick?

	// ...
}


void UTankAimingComponent::Initialise(UTankBarrel * BarreltoSet, UTankTurret * TurrettoSet)
{
	Barrel = BarreltoSet;
	Turret = TurrettoSet;
}

EFiringStatus UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

int32 UTankAimingComponent::getRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if(RoundsLeft<=0){
		FiringState = EFiringStatus::Default;
	}	
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeinSeconds) {
		FiringState = EFiringStatus::Reloading;
	}
	else if(IsBarrelMoving()){
		FiringState = EFiringStatus::Aiming;
	}
	else {
		FiringState = EFiringStatus::Ready;
	}
}


void UTankAimingComponent::BeginPlay()
{

	LastFireTime = GetWorld()->GetTimeSeconds();
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	return !(BarrelForward.Equals(AimDirection, 0.01));

}


void UTankAimingComponent::AimAt(FVector HitLocation)
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("aiming  at : %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);	
		//MoveBarrel();
	}
	else {
		auto time = GetWorld()->GetTimeSeconds();

		UE_LOG(LogTemp, Warning, TEXT("55no aim solve found %f"), time);		
	}	
}


void UTankAimingComponent::Fire()
{
	
	if (FiringState == EFiringStatus::Aiming || FiringState == EFiringStatus::Ready)
	{

		FVector location = Barrel->GetSocketLocation(FName("Projectile"));
		if (!ensure(Barrel )) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));


		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();

		RoundsLeft -=1;
	}

	if(NrOfBarrels == 3) {
		if (FiringState == EFiringStatus::Aiming || FiringState == EFiringStatus::Ready)
		{

			FVector location1 = Barrel->GetSocketLocation(FName("Projectile1"));
			if (!ensure(Barrel)) { return; }
			if (!ensure(ProjectileBlueprint)) { return; }
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile1")),
				Barrel->GetSocketRotation(FName("Projectile1")));


			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();

			RoundsLeft -= 1;
		}

		if (FiringState == EFiringStatus::Aiming || FiringState == EFiringStatus::Ready)
		{

			FVector location2 = Barrel->GetSocketLocation(FName("Projectile2"));

			if (!ensure(Barrel)) { return; }
			if (!ensure(ProjectileBlueprint)) { return; }
			auto Projectile = GetWorld()->SpawnActor<AProjectile>(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile2")),
				Barrel->GetSocketRotation(FName("Projectile2")));


			Projectile->LaunchProjectile(LaunchSpeed);
			LastFireTime = GetWorld()->GetTimeSeconds();

			RoundsLeft -= 1;
		}

	}

	

}





void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch); 
	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else {
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	
}











