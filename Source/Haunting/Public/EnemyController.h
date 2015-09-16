// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enemy.h"
#include "EnemyPathFollowingComponent.h"
#include "HauntingCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIController.h"
#include "RouteNode.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API AEnemyController : public AAIController
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(Transient)
	TSubobjectPtr<class UBlackboardComponent> BlackboardComp;

	UPROPERTY(Transient)
	TSubobjectPtr<class UBehaviorTreeComponent> BehaviorComp;

	virtual void Possess(class APawn* InPawn);

	void SetEnemy(class APawn *InPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchStuff();

	virtual void BeginPlay() override;

	uint8 EnemyKeyID;
	uint8 EnemyLocationID;
	
	//ARRAY THAT STORES THE PATH POINTS FOR SEARCHING
	TArray<ARouteNode*> RoutePoints;

protected:


	
	
};
