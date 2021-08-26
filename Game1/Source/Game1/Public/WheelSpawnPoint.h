// CopyRIght BitPatterns CyberSys

#pragma once
#include "SprungWheel.h"
#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WheelSpawnPoint.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME1_API UWheelSpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWheelSpawnPoint();

	AActor* GetSpawnedActor() const; 

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

	UPROPERTY()
	AActor *SpawnedActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
