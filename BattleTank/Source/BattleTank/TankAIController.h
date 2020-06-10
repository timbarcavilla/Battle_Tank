// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward declarations
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = Setup)
	float AcceptanceRadius = 5000;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DelatTime) override;
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDeath();

};
