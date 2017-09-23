// Copyright Breikdans Illusions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	// tiene que ser el ultimo en ser incluido

// Forward declaration
class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaTime) override;
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAmingComponent(UTankAimingComponent* AimCompRef);

private:
	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardsCrossHair();

	// return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

	UFUNCTION()
	void OnPossessedTankDeath();

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation	= 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation	= 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange		= 1000000.0f;

	UTankAimingComponent* AimingComponent = nullptr;
};
