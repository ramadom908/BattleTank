// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "WheelSpawnPoint.h"

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
	Super::BeginPlay();		

	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	//OnComponentHit.AddDynamic(this, &AMyBullet::OnHit);
}


//
//void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("I'm hit,,,, i'm hit"));
//	ApplySidewaysForce();
//	CurrentThrottle = 0;
//}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*>ResultArray;
	
	TArray<USceneComponent*>Children;

	GetChildrenComponents(true, Children);

	for (USceneComponent* Child : Children) {
		auto SpawnPointChild = Cast< UWheelSpawnPoint>(Child);
		if (!SpawnPointChild) continue;

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();

		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) continue;

		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}


////Removed after added wheels
//
//void UTankTrack::ApplySidewaysForce()
//{
//
//	//Removing sideways movement <<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>
//
//	//Calculate slipage speed
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//
//	//requiere acceleration this frame to correct
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
//
//	//Calculate and apply sideways
//	auto  TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//
//	auto CorrectionForece = TankRoot->GetMass()*CorectionAcceleration / 2; //Tow tracks
//	TankRoot->AddForce(CorrectionForece);
//}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied =  CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}

	//old stuff for track::::::::::::

	//auto ForceApplied = GetForwardVector()* CurrentThrottle * TrackMaxDrivingForce;
	//auto ForceLocation = GetComponentLocation();
	////ForceLocation = ForceLocation + FVector(50, 0, 80);  testing 

	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}




void UTankTrack::SetThrottle(float throttle) {

	float CurrentThrottle = FMath::Clamp<float>(throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}