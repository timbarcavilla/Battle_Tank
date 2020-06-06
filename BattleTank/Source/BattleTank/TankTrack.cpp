// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::Forward(float Throttle){
    auto Name = GetName();

    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}

void UTankTrack::Turn(float Scale)
{
    auto RotateSpeed = Scale * MaxRotatingSpeed;
    auto CurrentYaw = GetOwner()->GetRootComponent()->GetForwardVector().Rotation().Yaw;
    auto DeltaYaw = RotateSpeed * GetWorld()->DeltaTimeSeconds;
    auto NewYaw = CurrentYaw + DeltaYaw;
    GetOwner()->GetRootComponent()->SetRelativeRotation(FRotator(0.f, NewYaw, 0.f));
}
