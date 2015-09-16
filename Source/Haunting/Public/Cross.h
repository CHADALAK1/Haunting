//Cross.h
//The cross weapon contains an spherical AOE attack to stun the enemy inside the spherical AOE for a limited time

#pragma once

#include "Weapon.h"
#include "Enemy.h"
#include "FlashEffect.h"
#include "Cross.generated.h"

/**
 * 
 */
UCLASS()
class HAUNTING_API ACross : public AWeapon
{
	GENERATED_UCLASS_BODY()

	//AOE Sphere
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AOE)
	TSubobjectPtr<USphereComponent> AOECollisionComp;

	//Particle effect when firing weapon
	UPROPERTY(EditDefaultsOnly, Category = Flash)
	TSubclassOf<AFlashEffect> MuzzleFlash;

	//triggers AOE
	virtual void AOEFire() override;

	//turns off AOE after timer
	void AOEDisengage();

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;


	//Cooldown functions for Cross
	void Cooldown();
	void CooldownCheck();

	bool bIsFiring;
	bool bCanFire;

	//COLLISION DECLARATION PROTOTYPE
	UFUNCTION()
	void OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep);
};
