// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Applies forces onto tracks to move the tank. 
 */
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
protected:

	UFUNCTION(BlueprintCallable)
	void TrackStart();

private:

	UTankTrack();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void ApplySidewaysForce();
	void DriveTrack();

	float CurrentThrottle = 0;
};
