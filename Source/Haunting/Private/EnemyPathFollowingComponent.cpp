// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "Engine.h"
#include "AI/Navigation/NavAreas/NavArea.h"
#include "EnemyPathFollowingComponent.h"


UEnemyPathFollowingComponent::UEnemyPathFollowingComponent(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

}

void UEnemyPathFollowingComponent::SetMoveSegment(int32 SegmentStartIndex)
{
	Super::SetMoveSegment(SegmentStartIndex);

	if (CharacterMoveComp != NULL)
	{
		const FNavPathPoint& SegmentStart = Path->GetPathPoints()[MoveSegmentStartIndex];

		if (FNavAreaHelper::HasJumpFlag(SegmentStart))
		{
			CharacterMoveComp->SetMovementMode(MOVE_Flying);
		}
		else
		{
			CharacterMoveComp->SetMovementMode(MOVE_Walking);
		}
	}
}

void UEnemyPathFollowingComponent::SetMovementComponent(UNavMovementComponent* MoveComp)
{
	Super::SetMovementComponent(MoveComp);
	
	CharacterMoveComp = Cast<UCharacterMovementComponent>(MovementComp);
}