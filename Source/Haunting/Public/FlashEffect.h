// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ParticleDefinitions.h"
#include "FlashEffect.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API AFlashEffect : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Flash)
	TSubobjectPtr<UParticleSystemComponent> Flash;
	
};
