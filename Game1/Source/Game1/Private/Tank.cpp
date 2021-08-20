// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	//UE_LOG(LogTemp, Warning, TEXT("aim solve found 99"));
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed); //, LaunchSpeed

	
	
}

void ATank::Fire()
{
	auto time = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("Tank fires %f"), time);
}

//This  is set in the editor-> tank blupreint-> event graph -> method name
void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
}

//This  is set in the editor-> tank blupreint-> event graph -> method name
void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

