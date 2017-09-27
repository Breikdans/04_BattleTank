// Copyright Breikdans Illusions

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"	// so we can implement OnDeath

// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
		return;

	FoundAmingComponent(AimingComponent);
}

// esta funcion es llamada por el motor, cuando el Pawn es poseido.
// la usamos para suscribirnos al evento de OnDeath del tanque, 
// ya que en beginplay posiblemente aun no haya sido poseido el Pawn

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank))
			return;

		// TAREA: Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetPawn())	// if not possessing.... por ejemplo, cuando morimos y queremos ver desde algun tanque, pero ya no podemos poseer ninguno...
		return;

	if (!ensure(AimingComponent))
		return;

	FVector HitLocation(FVector::ZeroVector);	// Out Parameter
	if (GetSightRayHitLocation(HitLocation))	// Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}
}

// Get world location if linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	bool isSomethingHit = false;
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX=0, ViewportSizeY=0;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// "De-project the screen position of the crosshair to a world direction
	FVector LookDirection, CameraWorldLocation;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
			isSomethingHit = true;
	}
	
	return isSomethingHit;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;	// to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
										  ScreenLocation.Y, 
										  CameraWorldLocation, 
										  LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	// initialization of values to return
	bool IsHit = false;
	HitLocation = FVector(FVector::ZeroVector);

	IsHit = GetWorld()->LineTraceSingleByChannel(HitResult,
												 StartLocation,
												 EndLocation,
												 ECollisionChannel::ECC_Camera);
	if (IsHit)
		HitLocation = HitResult.Location;

	return IsHit;
}