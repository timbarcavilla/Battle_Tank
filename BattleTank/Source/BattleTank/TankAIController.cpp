// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    if (!GetPawn()) return;
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!AimingComponent){
        UE_LOG(LogTemp,Error,TEXT("Aiming Component not found on AI tank %s"), *GetOwner()->GetName());
    }
}

void ATankAIController::Tick(float DeltaTime){
    auto ControlledTank = GetPawn();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!ControlledTank || !PlayerTank) return;
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!AimingComponent) return;
    MoveToActor(PlayerTank, AcceptanceRadius);
    
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    //ControlledTank->Fire();
}
