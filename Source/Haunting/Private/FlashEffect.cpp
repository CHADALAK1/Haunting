// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "FlashEffect.h"


AFlashEffect::AFlashEffect(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Flash = PCIP.CreateDefaultSubobject<UParticleSystemComponent>(this, "Flash");
	RootComponent = Flash;
}


