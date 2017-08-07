// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet)
		return;

	LeftTrack	= LeftTrackToSet;
	RightTrack	= RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("Intend move forward: %f "), Throw);

	// para poner trazas de debug en pantalla y tener una alternativa a UE_LOG
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1,
										 0.35f,
										 FColor::Cyan.WithAlpha(150),
										 FString::Printf(TEXT("Intend move forward: %f "), Throw));
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	// TAREA prevent double speed due to dual control use (triggers and left stick)
}

