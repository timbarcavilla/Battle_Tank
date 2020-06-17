// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

class ATank;
class UParticleSystemComponent;
class URadialForceComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UProjectileMovementComponent* ProjMoveComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent *Explosion = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditAnywhere)
	float DestroyDelay = 10.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void LaunchProjectile(float LaunchSpeed, float Damage);
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);

	void OnTimerExpire();

	float ProjectileDamage = 0.f;

};
