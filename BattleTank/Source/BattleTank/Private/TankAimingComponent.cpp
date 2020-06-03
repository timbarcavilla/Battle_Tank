// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* SetBarrel){
	Barrel = SetBarrel;
}
void UTankAimingComponent::AimAt(FVector PlaceToAim, float LaunchSpeed){

	if (!Barrel) return;
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		PlaceToAim,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)){
		auto AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection){
	auto BarrelRotation = Barrel->GetForwardVector().Rotation
}
