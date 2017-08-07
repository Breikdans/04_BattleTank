// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"


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

}

