// Fill out your copyright notice in the Description page of Project Settings.


#include "Haunting.h"
#include "EnemyController.h"
#include "Enemy.h"


AEnemy::AEnemy(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AIControllerClass = AEnemyController::StaticClass();
	bIsSlowed = false;
	SlowTimer = 0.f;

}

void AEnemy::Slowed()
{
	CharacterMovement->MaxWalkSpeed = SlowSpeed;
	bIsSlowed = true;
	//GetWorldTimerManager().SetTimer(this, &AEnemy::UnSlowed, 1, false, 0.1f); <------- broken code
}

void AEnemy::CrossSlow()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "CrossSlowed");
	CharacterMovement->MaxWalkSpeed = 0.f;
	bIsSlowed = true;
}

void AEnemy::UnSlowed()
{
	CharacterMovement->MaxWalkSpeed = RecoverSpeed;
	bIsSlowed = false;
}

void AEnemy::Tick(float DeltaTime)
{
	if (bIsSlowed)
	{
		SlowTimer += 1.f;
		if (SlowTimer > 500.f)
		{
			UnSlowed();
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "UnSlowed");
		}
	}
	else
	{
		SlowTimer = 0.f;
	}
}