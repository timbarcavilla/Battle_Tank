// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetMobility(EComponentMobility::Movable);
	Axle->SetupAttachment(Spring);
	Axle->SetVisibility(true);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetMobility(EComponentMobility::Movable);
	Wheel->SetupAttachment(Axle);
	Wheel->SetVisibility(true);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	if (!Wheel) return;
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this,&ASprungWheel::OnHit);

	if (!Spring || !Wheel) return;
	Spring->SetConstrainedComponents(Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()),NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics){
		TotalForceMagnitudeThisFrame = 0.f;
	}

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude){
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit ){
	ApplyForce();
}

void ASprungWheel::ApplyForce(){
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}


