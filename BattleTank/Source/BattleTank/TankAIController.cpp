// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    if (!GetPawn()) return;
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!AimingComponent){
        UE_LOG(LogTemp,Error,TEXT("Aiming Component not found on AI tank %s"), *GetOwner()->GetName());
    }
}

void ATankAIController::SetPawn(APawn* InPawn){
    Super::SetPawn(InPawn);
    if (InPawn){
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank) return;

        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this,&ATankAIController::OnTankDeath);
    }
}

void ATankAIController::OnTankDeath(){
    UE_LOG(LogTemp,Warning,TEXT("AI is Dead"));

    auto ControlledTank = GetPawn();
    if (!ControlledTank) return;
    ControlledTank->DetachFromControllerPendingDestroy();
    
}


void ATankAIController::Tick(float DeltaTime){
    auto ControlledTank = GetPawn();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!ControlledTank || !PlayerTank) return;
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!AimingComponent) return;
    MoveToActor(PlayerTank, AcceptanceRadius);
    auto PlayerLocation = PlayerTank->GetActorLocation();
    PlayerLocation.Z += 35;
    AimingComponent->AimAt(PlayerLocation);

    FHitResult Hit;
    FVector PVPLocation;
    FRotator PVPRotation;
    GetPlayerViewPoint(
        PVPLocation,
        PVPRotation
    );
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, ControlledTank);
    GetWorld()->LineTraceSingleByObjectType(
        Hit,
        PVPLocation,
        PlayerLocation,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
        TraceParams);
    AActor *hitObject = Hit.GetActor();

    if (AimingComponent->GetFiringState() == EFiringState::Locked && !hitObject){
        AimingComponent->Fire();
    }
}
