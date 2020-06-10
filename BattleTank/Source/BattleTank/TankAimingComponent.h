// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class AProjectile;
class UTankBarrel;
class UTankTurret;

//Hold parameters for barrel's properties and elevate methods.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();	

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTurret* SetTurret, UTankBarrel* SetBarrel);

	void AimAt(FVector PlaceToAim);

	UFUNCTION(BlueprintCallable, Category = Fire)
	void Fire();

	EFiringState GetFiringState() const;

	UFUNCTION(BlueprintCallable, Category = Fire)
	int32 GetAmmo() const;

protected:

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(BlueprintReadWrite, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBP;

	UPROPERTY(EditDefaultsOnly, Category = State)
	int32 Ammo = 20;

private:

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	void MoveBarrel(FVector AimDirection);

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving() const;
	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 6000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 5;

	double LastFireTime = 0;

	FVector AimDirection= FVector(0.f,0.f,0.f);

};
