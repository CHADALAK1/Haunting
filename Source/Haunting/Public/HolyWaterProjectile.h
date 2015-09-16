// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WeaponProjectile.h"
#include "Enemy.h"
#include "HolyWaterProjectile.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API AHolyWaterProjectile : public AWeaponProjectile
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle)
	TSubobjectPtr<UParticleSystemComponent> WaterEffect;
	

	void OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
};
