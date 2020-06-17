// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

// Forward declarations
class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DelatTime) override;

	void IncreaseScore(int32 Increment);
	void DecreaseEnemyCount();

	UFUNCTION(BlueprintCallable, Category = Victory)
	void IncreaseLevel();

protected: 


	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundTank(ATank* TankRef);

	UFUNCTION(BlueprintImplementableEvent, Category = Death)
	void DisplayDeathMenu();

	UFUNCTION(BlueprintImplementableEvent, Category = Victory)
	void DisplayVictoryMenu();

	UFUNCTION(BlueprintImplementableEvent, Category = Victory)
	void LevelIncreased();

	UPROPERTY(BlueprintReadOnly, Category = Statistics)
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly, Category = Statistics)
	int32 Level = 1;

	UPROPERTY(BlueprintReadOnly, Category = Statistics)
	int32 EnemyCount = 0;

	UPROPERTY(BlueprintReadWrite, Category = Setup)
	TSubclassOf<ATank> TankBP;

private:
	void AimTowardsCrossHair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	virtual void SetPawn(APawn* InPawn) override;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 10000.f;

	TArray<FVector> SpawnPads = {
		FVector(23380,-19770,150),
		FVector(22600,5000,100),
		FVector(20200,15990,200),
		FVector(-22590,24580,50),
		FVector(-23970,-2230,180),
		FVector(-23370,-14480,2050),
	};

	UFUNCTION()
	void OnTankDeath();

	void SpawnEnemies();

	int32 CountSpawned = 0;

	float LastSpawnTime = 0;

	float SpawnRate = 30;

};
