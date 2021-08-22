// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Kismet/GameplayStatics.h"
#include "TankTurret.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus: uint8
{
	Default,
	Reloading,
	Aiming,
	Ready
	
};

//foward declaration
class UTankBarrel; 




// Holds barrels propreties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME1_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	void SetTurretReference(UTankTurret* TurretToSet);


public:	
	
	void AimAt(FVector HitLocation, float launchSpeed);


private:
	UTankBarrel * Barrel = nullptr;

	void MoveBarrelTowards(FVector AimDirection);

	UTankTurret* Turret = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Setup)
	EFiringStatus FiringState = EFiringStatus::Aiming;
		
};
