// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = true;
    SetNotifyRigidBodyCollision(true);
}

void UTankTrack::BeginPlay(){
    Super::BeginPlay();

}

void UTankTrack::TrackStart(){

    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

}

void UTankTrack::SetThrottle(float Throttle){
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle,-1,1);
}
void UTankTrack::DriveTrack(){
    auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}

void UTankTrack::ApplySidewaysForce(){
    auto SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
    
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector();

    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (CorrectionAcceleration * TankRoot->GetMass()) / 2;
    TankRoot->AddForce(CorrectionForce);
}