// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// tiene que ser el ultimo en ser incluido

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrossHair();

	// return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation	= 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation	= 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange		= 1000000.0f;
};
