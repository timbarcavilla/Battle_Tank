// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->SetupAttachment(RootComponent);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->SetupAttachment(RootComponent);
	ImpactBlast->SetAutoActivate(false);

	ProjMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjMoveComponent->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
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


void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit){
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

	UE_LOG(LogTemp,Warning,TEXT("Hit %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Warning, TEXT("Check %i"), OtherActor->IsRootComponentMovable());
	auto Origin = CollisionMesh->GetComponentLocation();
	if (OtherActor->IsRootComponentMovable()){
		Origin = OtherComp->GetComponentLocation();
	}
	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,
		Origin,
		ExplosionForce->Radius,
		UDamageType::StaticClass(),
		TArray<AActor *>() // damage all actors
	);
	ExplosionForce->FireImpulse();
	CollisionMesh->DestroyComponent();

	FTimerHandle Timer;

	GetWorld()->GetTimerManager().SetTimer(
		Timer,
		this,
		&AProjectile::OnTimerExpire,
		DestroyDelay,
		false
	);
}

void AProjectile::OnTimerExpire(){
	Destroy();
}
	


