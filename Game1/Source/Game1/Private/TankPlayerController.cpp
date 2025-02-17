// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
//#include "GameFramework/HUD.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()-> FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::SetPawn(APawn* InPawn) {

	Super::SetPawn(InPawn);

	if (InPawn) {

		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}

}

void ATankPlayerController::OnPossessedTankDeath() {

	StartSpectatingOnly();	
}



void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{

	if (!GetPawn()) { return; } // if not possesing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }


	FVector HitLocation; //out parameter
	if (GetSightRayHitLocation(HitLocation)) {

		AimingComponent->AimAt(HitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Screen location : %s"), *HitLocation.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
		//TODO aim ai that point
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	//find crosshair position
	auto ScreenLocation = FVector2D(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) {

		return GetLookVectorHitLocation(LookDirection, hitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Screen location : %s"), *hitLocation.ToString());
	}

	// line trace along that direction and see what we hit up to max range

	//hitLocation = FVector(1.0);

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection)const {
	// deproject the screen position of crosshair to a world direction
	FVector WorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
	FHitResult HitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (LookDirection* LineTraceRange);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, startLocation, endLocation, ECollisionChannel::ECC_Camera)) {
		HitLocation = HitResult.Location;
	//Draw debug a red trace in the world to visualise
	//FColor color = { 255, 0, 0, 0 }; // red
	//DrawDebugLine(GetWorld(), startLocation, HitLocation, color, false, -1.0f, 5, 1.f);
	return true;
	}

	HitLocation = FVector(0);
	return false;
}

