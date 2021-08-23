// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "GameFramework/Actor.h"
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
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float throttle);

	//TODO find max force per track
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000; // assume 40 tone tank and 1g acceleration
	UTankTrack();
	virtual void BeginPlay() override;
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void ApplySidewaysForce();
	void DriveTrack();

	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle=0;
	
};
