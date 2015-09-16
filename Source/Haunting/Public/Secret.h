// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Secret.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API ASecret : public APawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TSubobjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Light)
		TSubobjectPtr<UPointLightComponent> DemonLight;

	
	
};
