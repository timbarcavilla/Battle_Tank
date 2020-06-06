// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    
}

void ATankAIController::Tick(float DeltaTime){
    auto ControlledTank = Cast<ATank>(GetPawn());
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

    if (!ControlledTank || !PlayerTank) return;
    ControlledTank->AimAt(PlayerTank->GetActorLocation());
    //ControlledTank->Fire();
}
