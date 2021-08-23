// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank
 */
//UCLASS(meta = (BlueprintSpawnableComponent))
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME1_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float RelativeSpeed);


	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxDegreesPerSecond = 20;

	
};
