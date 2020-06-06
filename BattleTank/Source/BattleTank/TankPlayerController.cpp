// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank){
        UE_LOG(LogTemp, Error, TEXT("Tank not possessed"));
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *ControlledTank->GetName());
    }
}

void ATankPlayerController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair(){
    if (!GetControlledTank()) return;
    
    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)){
        GetControlledTank()->AimAt(HitLocation);
    }
    
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const{
    int32 VPsizeX, VPsizeY;
    GetViewportSize(VPsizeX,VPsizeY);

    FVector2D ScreenLocation = FVector2D(
        VPsizeX*CrossHairXLocation,
        VPsizeY*CrossHairYLocation
    );

    FVector WorldLocation, WorldDirection;
    if (DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        WorldLocation,
        WorldDirection
    )){
        FHitResult HitResult;
        if (GetWorld()->LineTraceSingleByChannel(
                HitResult,
                WorldLocation,
                WorldLocation + LineTraceRange * WorldDirection,
                ECollisionChannel::ECC_Visibility
                ))
        {
            OutHitLocation = HitResult.Location;
            return true;
        }
    }

    return false;
}
