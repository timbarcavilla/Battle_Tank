// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay(){
    Super::BeginPlay();
    if (!GetPawn()) return;
    auto ControlledTank = Cast<ATank>(GetPawn());
    if (ControlledTank){
        FoundTank(ControlledTank);
    }
    SpawnEnemies();
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
    StartSpectatingOnly();
    DetachFromPawn();
    DisplayDeathMenu();
}

void ATankPlayerController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    AimTowardsCrossHair();
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastSpawnTime >= SpawnRate && CountSpawned < Level){
        SpawnEnemies();
        LastSpawnTime = CurrentTime;
    }
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
                ECollisionChannel::ECC_Camera
                ))
        {
            OutHitLocation = HitResult.Location;
            return true;
        }
    }

    return false;
}

void ATankPlayerController::IncreaseScore(int32 Increment){
    Score += Increment;
}

void ATankPlayerController::IncreaseLevel(){
    ++Level;
    LevelIncreased();
    CountSpawned = 0;
    SpawnEnemies();
}

void ATankPlayerController::DecreaseEnemyCount(){
    --EnemyCount;
    if (EnemyCount <= 0 && CountSpawned >= Level)
    {
        DisplayVictoryMenu();
        IncreaseScore(1000);
    }
}

void ATankPlayerController::SpawnEnemies(){
    if (!TankBP) return;
    int32 Index = FMath::Rand() % 6;
    FVector SpawnPadLocation = SpawnPads[Index];
    UE_LOG(LogTemp, Warning, TEXT("Spawned at %s"), *SpawnPadLocation.ToString());

    FRotator SpawnPadRotation = FRotator(0,0,0);
    FActorSpawnParameters SpawnInfo;
    if (Index < 3){
        SpawnPadRotation = FRotator(0,180,0);
    }
    auto SpawnedTank = GetWorld()->SpawnActor<ATank>(
        TankBP,
        SpawnPadLocation,
        SpawnPadRotation,
        SpawnInfo
    );
    if (!SpawnedTank) return;
    ++EnemyCount;
    ++CountSpawned;
    LastSpawnTime = GetWorld()->GetTimeSeconds();
}

