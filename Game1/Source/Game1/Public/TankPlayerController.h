// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/Color.h"
#include "Engine.h"
//#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"


class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class GAME1_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	void BeginPlay() override;

	void SetPawn(APawn * InPawn);

	UFUNCTION()
	void OnPossessedTankDeath();

	virtual void Tick(float DeltaTime) override;

protected:


	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

private:
	//Move the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;



	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.334321;
 
};
