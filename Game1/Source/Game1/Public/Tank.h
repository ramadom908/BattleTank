// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class GAME1_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	virtual void BeginPlay() override;

	FTankDelegate OnDeath;

public:	
	virtual float TakeDamage(float DamageAmount,struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
	
	//
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

private:
	

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 120;
	
	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

};
