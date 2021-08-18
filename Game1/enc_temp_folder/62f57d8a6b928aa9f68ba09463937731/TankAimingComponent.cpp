// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OurTankName = GetOwner()->GetName(); //TODO remove

	auto barrelLocation=Barrel->GetComponentLocation(); //TODO remove
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at : %s"), *OurTankName, *HitLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at : %s"), *OurTankName, *barrelLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s aiming at : %s  from %s"), *OurTankName, *HitLocation.ToString(), *barrelLocation.ToString());
	



	if (!Barrel) { return;  }

	FVector OutLaunchVelocity{9,9,9};
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//SuggestProjectileVelocity

	//UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed);

	bool ok = UGameplayStatics::SuggestProjectileVelocity(
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::TraceFullPath);


	if (ok) {


		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		

		UE_LOG(LogTemp, Warning, TEXT("aiming  at : %s"), *AimDirection.ToString());
	}

	
}


void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;

}


