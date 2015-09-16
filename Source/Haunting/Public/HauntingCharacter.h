// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Item.h"
#include "Weapon.h"
#include "Torch.h"
#include "HolyWater.h"
#include "Cross.h"
#include "Tapestry.h"
#include "Enemy.h"
#include "Secret.h"
#include "HauntingCharacter.generated.h"

UCLASS(config=Game)
class AHauntingCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()


	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	TSubobjectPtr<class USkeletalMeshComponent> Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	TSubobjectPtr<UBoxComponent> CollisionComp;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;



	//INVENTORY ARRAY
	TArray<TSubclassOf<AWeapon>> Inventory;

	TSubclassOf<ATorch> TorchT;
	TSubclassOf<AHolyWater> HolyWaterT;
	TSubclassOf<ACross> CrossT;

	UPROPERTY(EditDefaultsOnly, Category = Secret)
	TSubclassOf<ASecret> Secret;

	//TEMPORARY VARIABLE TO STORE CURRENT WEAPON
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	AWeapon* CurrentWeapon;


	//FUNCTIONS TO EQUIP WEAPONS
	void EquipTorch();
	void EquipHolyWater();
	void EquipCross();

	virtual void BeginPlay() override;

	//COLLISION DECLARATION PROTOTYPE
	UFUNCTION()
	void OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep);

	//TAPESTRY COUNTER TO OPEN CATHEDRAL
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tapestry)
	int32 TapestryCounter;

protected:

	/** Handler for a touch input beginning. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Fires a projectile. */
	void OnFire();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

