// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	

	void AimAt(FVector PlaceToAim, float LaunchSpeed);

	void SetBarrelReference(UStaticMeshComponent* SetBarrel);

private:
	UStaticMeshComponent* Barrel = nullptr;
	void MoveBarrel(FVector AimDirection);
		
};