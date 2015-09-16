// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "Secret.h"


ASecret::ASecret(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, "Secret");
	RootComponent = Mesh;
	Mesh->SetRelativeRotation(FRotator(0, 90, 0));

	DemonLight = PCIP.CreateDefaultSubobject<UPointLightComponent>(this, "DemonLight");
	DemonLight->AttachTo(RootComponent);

	PrimaryActorTick.bCanEverTick = true;


}
