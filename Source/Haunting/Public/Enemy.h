// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API AEnemy : public ACharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* EnemyBehavior;

	void Slowed();
	void UnSlowed();
	void CrossSlow();
	virtual void Tick(float DeltaTime) override;

	bool bIsSlowed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterMovement)
	float RecoverSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterMovement)
	float SlowSpeed;

	float SlowTimer;
	
};
