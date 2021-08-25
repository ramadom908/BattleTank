// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Engine.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::SetPawn(APawn* InPawn) {

	Super::SetPawn(InPawn);

	if (InPawn) {

		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}

}

void ATankAIController::OnPossessedTankDeath() {

	UE_LOG(LogTemp, Warning, TEXT("OnPossessedTankDeath "));
	if (!GetPawn()) {
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
	
}


void ATankAIController::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) {
		return;
	}

		//TODO move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//aim towards the player
		//tell the controlled tank to aim ai player location
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (!ensure(AimingComponent)) { return; }

		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// fire if ready
		//TODO don't fire every frame
		
		if (AimingComponent->GetFiringState() == EFiringStatus::Ready) {
			AimingComponent->Fire(); //TODO de aici trag tancurile AI
		}

		

}