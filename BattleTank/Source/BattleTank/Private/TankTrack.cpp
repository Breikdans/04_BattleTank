// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Work-out the recquired acceleration this frame to correct
	auto CorrectionAcceleration = -(SlippageSpeed / DeltaTime * GetRightVector());

	// Calculate and apply sideways force F = m a
	auto TankMass = GetOwner()->GetRootPrimitiveComponent()->GetMass();
	auto CorrectionForce = (TankMass * CorrectionAcceleration) / 2;	// Two tracks

	GetOwner()->GetRootPrimitiveComponent()->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


