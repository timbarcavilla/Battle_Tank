// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay(){
    Super::BeginPlay();
    
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank){
        UE_LOG(LogTemp, Error, TEXT("The tank is not possessed"));
    }
    else{
        UE_LOG(LogTemp,Warning,TEXT("The tank is possessed by %s."),*ControlledTank->GetName());
    }

    auto PlayerTank = GetPlayerTank();
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Error, TEXT("The player tank is not possessed"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("The player tank is possessed by %s."), *PlayerTank->GetName());
    }
}

void ATankAIController::Tick(float DeltaTime){
    if (!GetControlledTank() || !GetPlayerTank()) return;
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const{
    auto PlayerTank = 
    Cast<ATankPlayerController>(GetWorld()->GetFirstPlayerController())->GetControlledTank();
    return PlayerTank;
}
