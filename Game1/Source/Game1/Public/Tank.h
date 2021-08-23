// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

//forward declarations class
class UTankBarrel;
class AProjectile;
//class UTankMovementComponent;

UCLASS()
class GAME1_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;



	/*UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;*/ //TODO remove?

public:	
	

	UFUNCTION(BlueprintCallable)
	void Fire();
	/*UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel * BarrelToSet);*/


private:
	//TODO remove launchspeed
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 7000.0;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float ReloadTimeinSeconds = 3.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;
	
	UTankBarrel* Barrel = nullptr; //local barrel reference for spawning projectile TODO remove

	float LastFireTime=0;

};
