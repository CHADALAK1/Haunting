// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "Item.h"


AItem::AItem(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, "Mesh");
	RootComponent = Mesh;

	CollisionComp = PCIP.CreateDefaultSubobject<UBoxComponent>(this, "CollisionComp");
	CollisionComp->AttachTo(RootComponent);
}
