// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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

void UTankAimingComponent::BeginPlay(){
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
	bool isReloading = (FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds;
	if (isReloading){
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving()){
		FiringState = EFiringState::Aiming;
	}
	else{
		FiringState = EFiringState::Locked;
	}

}

void UTankAimingComponent::Initialise(UTankTurret *SetTurret, UTankBarrel *SetBarrel){
	if (!SetTurret || !SetBarrel) return;
	Turret = SetTurret;
	Barrel = SetBarrel;
}

void UTankAimingComponent::AimAt(FVector PlaceToAim){

	if (!Barrel || !Turret) return;
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		PlaceToAim,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)){
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}
	
}

void UTankAimingComponent::Fire(){

	if (!Barrel || !ProjectileBP){
		UE_LOG(LogTemp,Error,TEXT("Barrel or ProjectileBP not set for %s"), *GetOwner()->GetName());
		return;
	}
	if (FiringState != EFiringState::Reloading){

		//Spawn
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);
		if (!Projectile){
			UE_LOG(LogTemp,Error,TEXT("Projectile not found for %s"), *GetOwner()->GetName());
			return;
		}
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection){

	if (!Barrel || !Turret) return;
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator-BarrelRotator;
	DeltaRotator = DeltaRotator.GetNormalized();

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
	
}

bool UTankAimingComponent::IsBarrelMoving() const{
 
	if (!Barrel) return false;
	auto BarrelDirection = Barrel->GetForwardVector().GetSafeNormal();
	return !BarrelDirection.Equals(AimDirection);
}