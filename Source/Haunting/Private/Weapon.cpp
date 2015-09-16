

#include "Haunting.h"
#include "Weapon.h"


AWeapon::AWeapon(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	Mesh = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, "Mesh");
	RootComponent = Mesh;

	CollisionComp = PCIP.CreateDefaultSubobject<UBoxComponent>(this, "CollisionComp");
}


void AWeapon::Fire()
{
	//switch statement checks for which type of projectile to use
	switch (ProjType)
	{
	case EProjectile::E_Projectile:
		ProjectileFire();
		break;
	case EProjectile::E_AOE:
		AOEFire();
		break;
	case EProjectile::E_None:
		NoFire();
	default:
		break;
	}
}

void AWeapon::ProjectileFire()
{

}

void AWeapon::AOEFire()
{

}

void AWeapon::NoFire()
{

}

