//Weapon.h
//Base weapon class for inheritance

#pragma once

#include "WeaponProjectile.h"
#include "Weapon.generated.h"

/**
 * 
 */

//Enum that can select the projectile type visually in blueprint.
UENUM(BlueprintType)
namespace EProjectile
{
	enum Type
	{
		E_Projectile			UMETA(DisplayName = "Projectile"),
		E_AOE					UMETA(DisplayName = "AOE"),
		E_None					UMETA(DisplayName = "None"),
	};
}



//struct for common variables in the weapon
USTRUCT(BlueprintType)
struct FWeaponConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 ShotCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float TimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float CurrentTimeBetweenShots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 WeaponRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FString Name;
};

UCLASS()
class HAUNTING_API AWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	TSubobjectPtr<UBoxComponent> CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	TEnumAsByte<EProjectile::Type> ProjType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh)
	TSubobjectPtr<USkeletalMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FWeaponConfig WeapConfig;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AWeaponProjectile> ProjectileClass;

	void Fire();

	//made the types of firing virtual for the sake of different ways to make the firing happen

	//fires projectile 
	virtual void ProjectileFire();

	//fires Area Of Effect
	virtual void AOEFire();

	//for non-firing events
	virtual void NoFire();

	FORCEINLINE void Pickup() { Destroy(); }
	
};
