// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "EnemyController.h"


AEnemyController::AEnemyController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP.SetDefaultSubobjectClass<UEnemyPathFollowingComponent>("PathFollowingComponent"))
{
	BlackboardComp = PCIP.CreateDefaultSubobject<UBlackboardComponent>(this, "BlackboardComp");

	BehaviorComp = PCIP.CreateDefaultSubobject<UBehaviorTreeComponent>(this, "BehaviorComp");

}

void AEnemyController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);
	AEnemy* Bot = Cast<AEnemy>(InPawn);
	if (Bot && Bot->EnemyBehavior)
	{
		BlackboardComp->InitializeBlackboard(Bot->EnemyBehavior->BlackboardAsset);

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		EnemyLocationID = BlackboardComp->GetKeyID("Destination");

		BehaviorComp->StartTree(Bot->EnemyBehavior);
	}
}

void AEnemyController::SearchForEnemy()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}
	
	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = 800.f;
	AHauntingCharacter* BestPawn = NULL;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AHauntingCharacter* TestPawn = Cast<AHauntingCharacter>(*It);
		if (TestPawn)
		{
			const float DistSq = FVector::Dist(TestPawn->GetActorLocation(), MyLoc);
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}

	}
	if (BestPawn)
	{
		SetEnemy(BestPawn);
	}
	else
	{
		SearchStuff();
	}
}

void AEnemyController::BeginPlay()
{
	for (TActorIterator<ARouteNode> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ARouteNode* TestNode = Cast<ARouteNode>(*ActorItr);
		if (TestNode)
		{
			RoutePoints.Add(TestNode);
			FString RouteName = TestNode->GetName();
		}
	}
}

void AEnemyController::SetEnemy(class APawn* InPawn)
{
	BlackboardComp->SetValueAsObject(EnemyKeyID, InPawn);
	BlackboardComp->SetValueAsVector(EnemyLocationID, InPawn->GetActorLocation());
}

void AEnemyController::SearchStuff()
{
	int32 RandomSeed = FMath::RandRange(0, 14);
	FRandomStream RouteRandomStream(RandomSeed);
	FString RouteName = FString::FromInt(RandomSeed);
	BlackboardComp->SetValueAsVector(EnemyLocationID, RoutePoints[RandomSeed]->GetActorLocation());
}
