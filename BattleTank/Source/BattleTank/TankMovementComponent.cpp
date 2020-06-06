// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* SetLeftTrack, UTankTrack* SetRightTrack){
    if (!SetLeftTrack || !SetRightTrack) return;
    LeftTrack = SetLeftTrack;
    RightTrack = SetRightTrack;
}


void UTankMovementComponent::IntendMoveForward(float Throw){
    UE_LOG(LogTemp,Warning,TEXT("Intend to move forward %f"), Throw);
    LeftTrack->Forward(Throw);
    RightTrack->Forward(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw){

    UE_LOG(LogTemp, Warning, TEXT("Intend to turn %f"), Throw);

    LeftTrack->Forward(Throw);
    RightTrack->Forward(-Throw);
}
