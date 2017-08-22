// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"

// Depends on movemement controller Via pathfinding system
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	
	if (!ensure(PlayerTank && ControlledTank && AimingComponent))
		return;

	// move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); // TAREA check radius is in centimetres

	// Aim towards the player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// TAREA Fix firing
	// Fire if ready
	//AimingComponent->Fire();	// TAREA limit firing rate
}
