// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Core/Public/Delegates/DelegateCombinations.h"
#include "Tank.generated.h"

// Forward declarations

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const &DamageEvent,
		class AController *EventInstigator,
		AActor *DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = Health)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = Health)
	void IncreaseHealthPercent(int32 Increment);

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	int32 StartingHealth = 100;
	
	int32 CurrentHealth;

public:
	FTankDelegate OnDeath;
};
