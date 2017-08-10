// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank && ControlledTank)
	{
		// move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // TAREA check radius is in centimetres
		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();	// TAREA limit firing rate
	}
}
