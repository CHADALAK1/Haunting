// Fill out your copyright notice in the Description page of Project Settings.

#include "Haunting.h"
#include "NavArea_Jump.h"


UNavArea_Jump::UNavArea_Jump(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	FNavAreaHelper::Set(AreaFlags, ENavAreaFlag::Jump);
}


