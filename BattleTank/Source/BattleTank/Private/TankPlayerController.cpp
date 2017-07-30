// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerControlledTank = GetControlledTank();
	if (PlayerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlled Tank: %s"), *PlayerControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is NO Player Controlled Tank!!"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrossHair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank())
		return;

	FVector HitLocation(FVector::ZeroVector);	// Out Parameter
	if (GetSightRayHitLocation(HitLocation))	// Has "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(HitLocation);
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
												 ECollisionChannel::ECC_Visibility);
	if (IsHit)
		HitLocation = HitResult.Location;

	return IsHit;
}