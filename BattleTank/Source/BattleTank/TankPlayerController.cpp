// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();
    if (!GetPawn()) return;
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (AimingComponent){
        FoundAimingComponent(AimingComponent);
        UE_LOG(LogTemp, Warning, TEXT("Aiming Component found!"));
    }
    else{
        UE_LOG(LogTemp,Error,TEXT("Aiming Component not found!"));
    }

}

void ATankPlayerController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank)
            return;

        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
    }
}

void ATankPlayerController::OnTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Player is Dead"));
    StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair(){
    if (!GetPawn()) return;
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!AimingComponent) return;
    FVector HitLocation;
    bool bSight = GetSightRayHitLocation(HitLocation);
    if (bSight)
    {
        AimingComponent->AimAt(HitLocation);
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
