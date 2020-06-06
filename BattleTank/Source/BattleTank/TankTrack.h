// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void Forward(float Throttle);

	UFUNCTION(BlueprintCallable, Category = Input)
	void Turn(float Scale);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 36000000.f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MaxRotatingSpeed = 10.f;
};
