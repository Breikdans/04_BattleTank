// Copyright Breikdans Illusions

#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("TANKES: [%s] Constructor ATank C++"), *TankName);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();	// Needed for BP Begin Play to run!!

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("TANKES: [%s] BeginPlay ATank C++"), *TankName);
}

void ATank::AimAt(const FVector& HitLocation)
{
	if (!ensure(TankAimingComponent))
		return;

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel))
		return;

	bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTimeInSeconds;

	if (IsReloaded)
	{
		// Spawn a projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
															  Barrel->GetSocketLocation(FName("Projectile")),
															  Barrel->GetSocketRotation(FName("Projectile")));

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}