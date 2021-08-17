// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());

	
}



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Test Begin play"));

	auto tank = GetControlledTank();

	if (tank) {

		UE_LOG(LogTemp, Warning, TEXT("Test Begin play %s"), *tank->GetName());
	}

	

}
