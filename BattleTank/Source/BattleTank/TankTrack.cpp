// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "TankTrack.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = true;
    SetNotifyRigidBodyCollision(true);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction){
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

}

void UTankTrack::SetThrottle(float Throttle){
    float CurrentThrottle = FMath::Clamp<float>(Throttle,-1,1);
    DriveTrack(CurrentThrottle);
}
void UTankTrack::DriveTrack(float CurrentThrottle){
    auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
    auto Wheels = GetWheels();
    auto ForcePerWheel = ForceApplied / Wheels.Num();
    for (ASprungWheel* Wheel:Wheels){
        Wheel->AddDrivingForce(ForcePerWheel);
    }
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const{
    TArray<USceneComponent*> SpawnPoints;
    GetChildrenComponents(false,SpawnPoints);

    TArray<ASprungWheel*> Wheels;
    for (USceneComponent* Point:SpawnPoints){
        auto SpawnPoint = Cast<USpawnPoint>(Point);
        Wheels.Emplace(SpawnPoint->GetWheel());
    }

    return Wheels;
}