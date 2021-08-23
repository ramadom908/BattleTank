// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent)) 
class GAME1_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 max downward movement + 1 = max up
	void Elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 10; 

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationDegrees = 0; 

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationDegrees = 40; 

};
