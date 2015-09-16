// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "Torch.h"


ATorch::ATorch(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Flame = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, "Flame");
	Flame->AttachTo(RootComponent);

	WeapConfig.Name = "Torch";
}


void ATorch::NoFire()
{
	Super::NoFire();

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "TORCH MEEEEE!");
}