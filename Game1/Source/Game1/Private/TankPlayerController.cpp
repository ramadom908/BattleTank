// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
//#include "GameFramework/HUD.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	/*UE_LOG(LogTemp, Warning, TEXT("Test Begin play"));

	auto tank = GetControlledTank();

	if (tank) {

		UE_LOG(LogTemp, Warning, TEXT("Test Begin play %s"), *tank->GetName());
	}*/

	

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}


	FVector HitLocation; //out parameter
	if (GetSightRayHitLocation(HitLocation)) {

		GetControlledTank()->AimAt(HitLocation);
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

		GetLookVectorHitLocation(LookDirection, hitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Screen location : %s"), *hitLocation.ToString());
	}

	// line trace along that direction and see what we hit up to max range

	//hitLocation = FVector(1.0);

	return true;
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
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
	//Draw debug a red trace in the world to visualise
	//FColor color = { 255, 0, 0, 0 }; // red
	//DrawDebugLine(GetWorld(), startLocation, HitLocation, color, false, -1.0f, 5, 1.f);
	return true;
	}

	HitLocation = FVector(0);
	return false;
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
