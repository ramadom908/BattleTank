// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("Test Begin play"));

	auto tank = GetControlledTank();

	if (tank) {

		UE_LOG(LogTemp, Warning, TEXT("AI Tank name is %s"), *tank->GetName());
	}



}