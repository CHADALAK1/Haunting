

#include "Haunting.h"
#include "HolyWater.h"


AHolyWater::AHolyWater(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	WeapConfig.Name = "Holy Water";
}

void AHolyWater::BeginPlay()
{
	bCanFire = true;
}

void AHolyWater::ProjectileFire()
{
	Super::ProjectileFire();

	if (bCanFire)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "OW HOLY WATER!");

		FVector CameraLoc;
		FRotator CameraRot;
		FVector MuzzleLoc = Mesh->GetSocketLocation("WS");
		FRotator MuzzleRot = Mesh->GetSocketRotation("WS");
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		AWeaponProjectile* Projectile = GetWorld()->SpawnActor<AWeaponProjectile>(ProjectileClass, MuzzleLoc, MuzzleRot, SpawnParams);
		Cooldown();
	}
	else
	{
		bCanFire = false;
	}
}

void AHolyWater::Tick(float DeltaSeconds)
{
	if (WeapConfig.CurrentTimeBetweenShots > 0.f)
	{
		WeapConfig.CurrentTimeBetweenShots -= DeltaSeconds;
	}
	else
	{
		WeapConfig.CurrentTimeBetweenShots = 0.f;
	}
}

void AHolyWater::Cooldown()
{
	bCanFire = false;
	FTimerHandle MyHandle;
	GetWorldTimerManager().SetTimer(MyHandle, this, &AHolyWater::CooldownCheck, WeapConfig.TimeBetweenShots, false);
	WeapConfig.CurrentTimeBetweenShots = GetWorldTimerManager().GetTimerRemaining(MyHandle);
}

void AHolyWater::CooldownCheck()
{
	bCanFire = true;
}