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

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
