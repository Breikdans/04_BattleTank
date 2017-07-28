// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AIControlledTank = GetControlledTank();
	if (AIControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank: %s"), *AIControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is NO AI Controlled Tank!!"));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

