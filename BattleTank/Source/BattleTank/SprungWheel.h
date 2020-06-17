// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	void AddDrivingForce(float ForceMagnitude);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent *Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent *Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent *Spring = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPhysicsConstraintComponent *AxleWheelConstraint = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0.f;
};
