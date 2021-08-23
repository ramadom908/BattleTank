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
class UTankTurret;
class AProjectile;

// Holds barrels propreties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME1_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarreltoSet, UTankTurret* TurrettoSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus FiringState = EFiringStatus::Reloading;


private:
	UTankAimingComponent();
	void MoveBarrelTowards(FVector AimDirection);

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving();

	UTankTurret* Turret = nullptr;
	UTankBarrel * Barrel = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 7000.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeinSeconds = 3.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	float LastFireTime = 0;

	FVector AimDirection;
		
};
