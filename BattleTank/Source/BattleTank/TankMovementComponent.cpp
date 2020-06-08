// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* SetLeftTrack, UTankTrack* SetRightTrack){
    if (!SetLeftTrack || !SetRightTrack) return;
    LeftTrack = SetLeftTrack;
    RightTrack = SetRightTrack;
}


void UTankMovementComponent::IntendMoveForward(float Throw){
    if (!LeftTrack || !RightTrack) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurn(float Throw){

    if (!LeftTrack || !RightTrack) return;
    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed){
    
    auto TankDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();

    float DotProduct = FVector::DotProduct(AIForwardIntention, TankDirection);
    float CrossProduct = FVector::CrossProduct(AIForwardIntention, TankDirection).Z;
    IntendMoveForward(DotProduct);
    IntendTurn(CrossProduct);

}
