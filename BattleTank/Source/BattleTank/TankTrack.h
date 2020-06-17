// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Applies forces onto tracks to move the tank. 
 */
class ASprungWheel;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))

class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 38000000.f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MaxRotatingSpeed = 10.f;

private:

	UTankTrack();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void DriveTrack(float CurrentThrottle);

	TArray<ASprungWheel*> GetWheels() const;

	
};
