// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class GAME1_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	
	void BeginPlay() override;
private:
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn)override;

	UFUNCTION()
	void OnPossessedTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 8000.f;
};
