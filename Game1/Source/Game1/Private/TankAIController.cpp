// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//auto tank = GetControlledTank();

	//if (tank) {

	//	UE_LOG(LogTemp, Warning, TEXT("AI Tank name is %s"), *tank->GetName());
	//}
}


void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank) {

		//TODO move towards the player

		//aim towards the player
		//tell the controlled tank to aim ai player location
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// fire if ready
		//TODO don't fire every frame
		ControlledTank->Fire(); //TODO de aici trag tancurile AI

	}

	
	

	//AimTowardsCrosshair();
}