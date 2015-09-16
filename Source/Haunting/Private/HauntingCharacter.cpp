// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Haunting.h"
#include "HauntingCharacter.h"
#include "HauntingProjectile.h"
#include "Animation/AnimInstance.h"


//////////////////////////////////////////////////////////////////////////
// AHauntingCharacter

AHauntingCharacter::AHauntingCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{

	static ConstructorHelpers::FObjectFinder<UBlueprint> TorchBlueprint(TEXT("Blueprint'/Game/Blueprints/Weapon/Torch_BP.Torch_BP'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> CrossBlueprint(TEXT("Blueprint'/Game/Blueprints/Weapon/Cross_BP.Cross_BP'"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> HolyWaterBlueprint(TEXT("Blueprint'/Game/Blueprints/Weapon/HolyWater_Bp.HolyWater_BP'"));
	if (TorchBlueprint.Object)
	{
		TorchT = (UClass*)TorchBlueprint.Object->GeneratedClass;
	}
	if (CrossBlueprint.Object)
	{
		CrossT = (UClass*)CrossBlueprint.Object->GeneratedClass;
	}
	if (HolyWaterBlueprint.Object)
	{
		HolyWaterT = (UClass*)HolyWaterBlueprint.Object->GeneratedClass;
	}

	CurrentWeapon = NULL;

	// Set size for collision capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	CollisionComp = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionComp"));
	CollisionComp->AttachTo(RootComponent);
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AHauntingCharacter::OnCollision);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->AttachParent = CapsuleComponent;
	FirstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 30.0f, 10.0f);

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = PCIP.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->AttachParent = FirstPersonCameraComponent;
	Mesh1P->RelativeLocation = FVector(0.f, 0.f, -150.f);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P are set in the
	// derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHauntingCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("HolyWater", IE_Pressed, this, &AHauntingCharacter::EquipHolyWater);
	InputComponent->BindAction("Torch", IE_Pressed, this, &AHauntingCharacter::EquipTorch);
	InputComponent->BindAction("Cross", IE_Pressed, this, &AHauntingCharacter::EquipCross);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AHauntingCharacter::OnFire);
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AHauntingCharacter::TouchStarted);

	InputComponent->BindAxis("MoveForward", this, &AHauntingCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AHauntingCharacter::MoveRight);
	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AHauntingCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AHauntingCharacter::LookUpAtRate);
}

void AHauntingCharacter::OnFire()
{
	CurrentWeapon->Fire();
}

void AHauntingCharacter::EquipTorch()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Pickup();
	}
	ATorch* Spawn = GetWorld()->SpawnActor<ATorch>(Inventory[0]);
	if (Spawn)
	{
		CurrentWeapon = Spawn;
		Spawn->CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Spawn->AttachRootComponentTo(Mesh1P, "WS", EAttachLocation::SnapToTarget);
	}
}

void AHauntingCharacter::EquipHolyWater()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Pickup();
	}
	AHolyWater* Spawn = GetWorld()->SpawnActor<AHolyWater>(Inventory[1]);
	if (Spawn)
	{
		CurrentWeapon = Spawn;
		Spawn->CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Spawn->AttachRootComponentTo(Mesh1P, "WS", EAttachLocation::SnapToTarget);
	}
}

void AHauntingCharacter::EquipCross()
{
	if (CurrentWeapon != NULL)
	{
		CurrentWeapon->Pickup();
	}
	ACross* Spawn = GetWorld()->SpawnActor<ACross>(Inventory[2]);
	if (Spawn)
	{
		CurrentWeapon = Spawn;
		Spawn->CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Spawn->AttachRootComponentTo(Mesh1P, "WS", EAttachLocation::KeepRelativeOffset);
	}
}

void AHauntingCharacter::BeginPlay()
{
	ATorch* TSpawn = GetWorld()->SpawnActor<ATorch>(TorchT);
	if (TSpawn)
	{
		Inventory.Push(TorchT);
		FString TName = TorchT->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, TName);
	}
	AHolyWater* HSpawn = GetWorld()->SpawnActor<AHolyWater>(HolyWaterT);
	if (HSpawn)
	{
		Inventory.Push(HolyWaterT);
		FString HName = HolyWaterT->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, HName);
	}
	ACross* CSpawn = GetWorld()->SpawnActor<ACross>(CrossT);
	if (HSpawn)
	{
		Inventory.Push(CrossT);
		FString CName = CrossT->GetName();
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Blue, CName);
	}

	CSpawn->Pickup();
	TSpawn->Pickup();
	HSpawn->Pickup();

	EquipTorch();
}

void AHauntingCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// only fire for first finger down
	if (FingerIndex == 0)
	{
		OnFire();
	}
}

void AHauntingCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHauntingCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHauntingCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHauntingCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHauntingCharacter::OnCollision(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Sweep)
{
	ATapestry* Tap = Cast<ATapestry>(OtherActor);
	if (Tap)
	{
		Tap->Pickup();
		if (TapestryCounter < 6)
		{
			TapestryCounter++;
			FString CounterCheck = FString::FromInt(TapestryCounter);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, CounterCheck);
		}
		if (TapestryCounter == 4)
		{
			/*ASecret* Bear = GetWorld()->SpawnActor<ASecret>(Secret, FVector(324.457092, -980.027283, 117.816895), FRotator(0, 0, 0));
			ASecret* Bear2 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(1815.868164, -2362.319336, 107.266891), FRotator(0, -90.0f, 0));
			ASecret* Bear3 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(1781.89502, -912.455994, 107.266663), FRotator(0, -90.0f, 0));
			ASecret* Bear4 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(1808.952881, -648.31488, 107.266663), FRotator(0, -90.0f, 0));
			ASecret* Bear5 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(990.646973, -376.725037, 92.343254), FRotator(0, -90.0f, 0));
			ASecret* Bear6 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(-848.70874, -1488.191406, 106.832359), FRotator(0, 0, 0));
			ASecret* Bear7 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(-1190.120972, -2534.654297, 107.568062), FRotator(0, -90.0f, 0));
			ASecret* Bear8 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(-1190.120972, -2919.340088, 107.568062), FRotator(0, -90.0f, 0));
			ASecret* Bear9 = GetWorld()->SpawnActor<ASecret>(Secret, FVector(-1190.120972, -3376.745361, 107.568062), FRotator(0, -90.0f, 0));
			*/
			
		}
		
		if (TapestryCounter == 6)
		{
			UGameplayStatics::OpenLevel(GetWorld(), "Winner", false, "");
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "YOU WON!");
		}
	}
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "GameOver", false, "");
	}
}
