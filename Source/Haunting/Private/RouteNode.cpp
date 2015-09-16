// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "EnemyController.h"
#include "RouteNode.h"


ARouteNode::ARouteNode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	CollisionComp = PCIP.CreateDefaultSubobject<UBoxComponent>(this, "CollisionComp");
	RootComponent = CollisionComp;

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ARouteNode::OnCollision);
}


void ARouteNode::OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	AEnemyController* Enemy = Cast<AEnemyController>(OtherActor);

	if (Enemy)
	{
		Enemy->BlackboardComp->SetValueAsObject(Enemy->EnemyKeyID, this->GetClass());
	}
}