// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Torch.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API ATorch : public AWeapon
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Flame)
	TSubobjectPtr<UParticleSystemComponent> Flame;

	virtual void NoFire() override;
	
};
