

#include "Haunting.h"
#include "Cross.h"


ACross::ACross(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	AOECollisionComp = PCIP.CreateDefaultSubobject<USphereComponent>(this, "AOE");
	AOECollisionComp->AttachTo(RootComponent);
	AOECollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACross::OnCollision);

	AOECollisionComp->SetSphereRadius(0.f, false);
	bIsFiring = false;
	PrimaryActorTick.bCanEverTick = true;

	WeapConfig.Name = "Cross";
}

void ACross::AOEFire()
{
	if (bCanFire)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "CROSSSSSSS!");
		AOECollisionComp->SetSphereRadius(500.f, true);
		bIsFiring = true;
		FVector FlashLoc = Mesh->GetSocketLocation("WS");
		FRotator FlashRot = Mesh->GetSocketRotation("WS");
		AFlashEffect* Flash = GetWorld()->SpawnActor<AFlashEffect>(MuzzleFlash,FlashLoc,FlashRot);
		FTimerHandle MyHandle;
		GetWorldTimerManager().SetTimer(MyHandle, this, &ACross::AOEDisengage, 2.0f, false);
	}
	else
	{
		bIsFiring = false;
	}
}

void ACross::BeginPlay()
{
	bIsFiring = false;
	bCanFire = true;
}

void ACross::Tick(float DeltaSeconds)
{
	if (WeapConfig.CurrentTimeBetweenShots > 0.f)
	{
		FTimerDelegate MyDelegate;
		WeapConfig.CurrentTimeBetweenShots -= DeltaSeconds;
	}
	else
	{
		WeapConfig.CurrentTimeBetweenShots = 0.f;
	}
}

void ACross::AOEDisengage()
{
	AOECollisionComp->SetSphereRadius(0.f, false);
	bIsFiring = false;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "UnCross");
	bCanFire = false;
	Cooldown();
}


void ACross::OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->CrossSlow();
	}
}

void ACross::Cooldown()
{
	if (!bCanFire)
	{
		FString TimeCheck = FString::FromInt(WeapConfig.TimeBetweenShots);
		FTimerHandle MyHandle;
		GetWorldTimerManager().SetTimer(MyHandle,this, &ACross::CooldownCheck, WeapConfig.TimeBetweenShots, false);
		WeapConfig.CurrentTimeBetweenShots = GetWorldTimerManager().GetTimerRemaining(MyHandle);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green,  TimeCheck + " sec Cooldown");

	}
	else
	{
		bCanFire = true;
	}
}

void ACross::CooldownCheck()
{
	bCanFire = true;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Cross Ready");
}