// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!LeftTrack || !RightTrack) {
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) {
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//No need to call super as we're replacing functionality

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);


	auto RightMoveThrow = FVector::CrossProduct(TankForward, AIForwardIntention);
	IntendTurnRight(RightMoveThrow.Z);

	//UE_LOG(LogTemp, Warning, TEXT("right: %f, forward %f"), RightMoveThrow.Z, ForwardThrow);

}



void UTankMovementComponent::Initialise(UTankTrack * LeftTracktoSet, UTankTrack * RightTracktoSet)
{
	LeftTrack = LeftTracktoSet;
	RightTrack = RightTracktoSet;
}
