// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Navigation/PathFollowingComponent.h"
#include "NavArea_Jump.h"
#include "EnemyPathFollowingComponent.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API UEnemyPathFollowingComponent : public UPathFollowingComponent
{
	GENERATED_UCLASS_BODY()


	virtual void SetMoveSegment(int32 SegmentStartIndex) override;

	virtual void SetMovementComponent(UNavMovementComponent* MoveComp) override;


protected:
	UPROPERTY(Transient)
	UCharacterMovementComponent* CharacterMoveComp;


	
};
