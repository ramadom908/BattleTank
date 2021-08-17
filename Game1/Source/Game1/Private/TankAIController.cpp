// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
	
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerController = GetWorld()->GetFirstPlayerController()->GetPawn();
	//UE_LOG(LogExec, Warning, TEXT("GetControlledTank() was called."));
	//daca nu pun linia asta de aici unreal optimizeaza functia asta si nu o sa intre in ea in debug mode
	return Cast<ATank>(PlayerController);
	
}



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto tank = GetControlledTank();

	if (tank) {

		UE_LOG(LogTemp, Warning, TEXT("AI Tank name is %s"), *tank->GetName());
	}

	auto tank2 = GetPlayerTank();

	if (tank2) {

		UE_LOG(LogTemp, Warning, TEXT("AI Tank found player %s"), *tank2->GetName());
	}

}