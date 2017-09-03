// Copyright Breikdans Illusions

#include "Tank.h"
// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

float ATank::TakeDamage(float DamageAmount,
						struct FDamageEvent const & DamageEvent,
						class AController * EventInstigator,
						AActor * DamageCauser)
{

	// Con DamageAmount, aplica el daño por defecto especificado (20)
//	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);

	// Llamando a la funcion de la clase padre y recogiendo el resultado, nos da el daño inglingido, segun el radio del impacto, MOLA MAS!!
	int32 DamagePoints = FPlatformMath::RoundToInt(Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser));
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	auto TankName = GetName();
	//// para poner trazas de debug en pantalla y tener una alternativa a UE_LOG
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1,
										 10.0f,
										 FColor::Cyan.WithAlpha(150),
										 FString::Printf(TEXT("Tank:(%s). CurrentHealth:(%d) DamageToApply(%d)"), *TankName, CurrentHealth, DamageToApply));

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
		GEngine->AddOnScreenDebugMessage(-1,
										 10.0f,
										 FColor::Red.WithAlpha(150),
										 FString::Printf(TEXT("Tank:(%s). Died!!!"), *TankName));

	return DamageToApply;
}