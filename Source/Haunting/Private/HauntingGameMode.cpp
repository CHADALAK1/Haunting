// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Haunting.h"
#include "HauntingGameMode.h"
#include "HauntingHUD.h"
#include "HauntingCharacter.h"

AHauntingGameMode::AHauntingGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHauntingHUD::StaticClass();
}
