// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjMoveComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float LaunchSpeed){
	UE_LOG(LogTemp,Warning,TEXT("Launched at %f"), LaunchSpeed);
	if (!ProjMoveComponent){
		UE_LOG(LogTemp, Error, TEXT("Projectile not set for %s"), *GetOwner()->GetName());
		return;
	}
	ProjMoveComponent->SetVelocityInLocalSpace(FVector::ForwardVector*LaunchSpeed);
	ProjMoveComponent->Activate();
}


