

#pragma once

#include "Weapon.h"
#include "HolyWater.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API AHolyWater : public AWeapon
{
	GENERATED_UCLASS_BODY()

	virtual void ProjectileFire() override;

	void Cooldown();
	void CooldownCheck();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	bool bCanFire;
	bool bIsFiring;
	
};
