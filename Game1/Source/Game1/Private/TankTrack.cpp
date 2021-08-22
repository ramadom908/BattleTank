// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle) {

	
	auto time = GetWorld()->GetTimeSeconds();

	UE_LOG(LogTemp, Warning, TEXT("%s throttle %f"), *GetName(), time);

	auto ForceApplied = GetForwardVector()* throttle * TrackMaxDrivingForce;

	auto ForceLocation = GetComponentLocation();
	ForceLocation = ForceLocation + FVector(50, 0, 80);

	UE_LOG(LogTemp, Warning, TEXT("%s trck location: %s"), *GetName(), *ForceLocation.ToString() );
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	//AddForceAtLocation(ForceApplied, ForceLocation);


	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}