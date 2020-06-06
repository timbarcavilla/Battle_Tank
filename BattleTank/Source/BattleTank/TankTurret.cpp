// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RotateSpeed){
    RotateSpeed = FMath::Clamp<float>(RotateSpeed,-1,1);
    float DeltaRotation = RotateSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float NewYaw = RelativeRotation.Yaw + DeltaRotation;
    SetRelativeRotation(FRotator(0.f,NewYaw,0.f));
}