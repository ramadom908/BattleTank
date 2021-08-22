// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
//UCLASS(meta = (BlueprintSpawnableComponent))
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAME1_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);

	//TODO find max force per track
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // assume 40 tone tank and 1g acceleration

	
	
};
