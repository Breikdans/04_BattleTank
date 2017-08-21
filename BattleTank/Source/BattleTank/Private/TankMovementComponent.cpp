// Copyright Breikdans Illusions

#include "TankMovementComponent.h"
#include "TankTrack.h"

// Se incluyen estos dos para que funcione correctamente intellisense... sino no encontraba GetWorld() ni GEngine y no funcionaba
#include "Engine/World.h"
#include "Engine/Engine.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack	= LeftTrackToSet;
	RightTrack	= RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super()!!

	//auto TankName = GetOwner()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("Tank: %s. move velocity: %s "), *TankName, *MoveVelocity.ToString());

	//// para poner trazas de debug en pantalla y tener una alternativa a UE_LOG
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1,
	//									 0.35f,
	//									 FColor::Cyan.WithAlpha(150),
	//									 FString::Printf(TEXT("Tank: %s. move velocity: %s "), *TankName, *MoveVelocity.ToString()));

	// Normalizamos vectores
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	// calculamos el Dot Product = Producto Escalar.
	// El producto escalar, nos da un ESCALAR indicando el grado de "paralelismo" entre 2 vectores, devolviendo valores entre 1..0..-1:
	//		1: Si los vectores son paralelos y van en el mismo sentido
	//      0: Si los vectores son perpendiculares
	//     -1: Si los vectores son paralelos PERO van en sentido opuesto
	// Asi, por ejemplo, si el vector de intencion ya es igual al de direccion, nuestra velocidad de avance sera total, o sea 1.
	// SE UTILIZA PARA CALCULAR LA VELOCIDAD DE AVANCE/RETROCESO
	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	// calculamos el Cross Product = Producto Vectorial.
	// El producto vectorial, nos da un VECTOR indicando el grado de "perpendicularidad" entre 2 vectores, 
	// devolviendo valores EN EL EJE Z, entre 1..0..-1:
	//		1: Si los vectores son perpendiculares y dependiendo de cual de los 2 se haya multiplicado por el otro
	//      0: Si los vectores son paralelos 
	//     -1: Si los vectores son perpendiculares y dependiendo de cual de los 2 se haya multiplicado por el otro (lado contrario)
	// Asi, por ejemplo, si el vector de intencion es perpendicular al de direccion, nuestra velocidad de giro sera total, o sea 1.
	// SE UTILIZA PARA CALCULAR LA VELOCIDAD DE GIRO
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
}
void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack))
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
