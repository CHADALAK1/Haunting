// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "HolyWaterProjectile.h"


AHolyWaterProjectile::AHolyWaterProjectile(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	WaterEffect = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, "WaterEffect");
	WaterEffect->AttachTo(RootComponent);
}

void AHolyWaterProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->Slowed();
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "SLOWED");
	}
	if (OtherActor != NULL)
	{
		Destroy();
	}
}
