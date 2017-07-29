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

	auto PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found Player Tank: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("There is NO Player Tank!!"));
	}

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetPlayerTank();
	auto ControlledTank = GetControlledTank();

	if (ControlledTank && PlayerTank)
	{
		// TAREA move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}