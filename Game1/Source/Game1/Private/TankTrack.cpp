// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;

}

//
//void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);
//
//	UE_LOG(LogTemp, Warning, TEXT("track tick"));
//}



void UTankTrack::BeginPlay()
{

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	//OnComponentHit.AddDynamic(this, &AMyBullet::OnHit);
}



void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("I'm hit,,,, i'm hit"));

	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}


void UTankTrack::ApplySidewaysForce()
{

	//Removing sideways movement <<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>

	//Calculate slipage speed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//requiere acceleration this frame to correct
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Calculate and apply sideways
	auto  TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	auto CorrectionForece = TankRoot->GetMass()*CorectionAcceleration / 2; //Tow tracks
	TankRoot->AddForce(CorrectionForece);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector()* CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	//ForceLocation = ForceLocation + FVector(50, 0, 80);  testing 

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}




void UTankTrack::SetThrottle(float throttle) {

	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + throttle, -1, 1);
}