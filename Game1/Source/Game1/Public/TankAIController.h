// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
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
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
	virtual void Tick(float DeltaTime) override;
	
};
