// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperCharacterClass.h"

#include "ChargedProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "SaveGameClass.h"
#include "ChargingBull.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ShotActionInterface.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASuperCharacterClass::ASuperCharacterClass()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SpringArm Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 0;
	SpringArmComp->SocketOffset = FVector(0, 0, 0);
	SpringArmComp->SetRelativeRotation(FRotator(0, 0, 0));

	//Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->SetRelativeRotation(FRotator(0, 0, 0));
	CameraComp->SetProjectionMode(ECameraProjectionMode::Perspective);

	//Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	MeshComp->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	EffectLocation = CreateDefaultSubobject<USceneComponent>("ShotChargeEffect");
	EffectLocation->SetupAttachment(CameraComp);
}

// Called when the game starts or when spawned
void ASuperCharacterClass::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;

	DashCurrentCooldown = DashMaxCooldown;
	PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
			PC->GetLocalPlayer());
		if (SubSystem)
		{
			SubSystem->AddMappingContext(PlayerMapping, 0);
		}
		PC->SetControlRotation(GetActorRotation());
	}
	SpawnPoint = GetActorLocation();

	UGameplayStatics::DeleteGameInSlot("MySaveSlot", 0);
}

// Called every frame
void ASuperCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CooldownsHandler(DeltaTime);

	if (bIsDashing)
		DashInterpolation(DeltaTime);

	UE_LOG(LogTemp,Warning,TEXT("%f,%f"),GetActorForwardVector().X,GetActorForwardVector().Y);
	
}

// Called to bind functionality to input
void ASuperCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Bind Axis
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASuperCharacterClass::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASuperCharacterClass::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASuperCharacterClass::Jump);

		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Triggered, this, &ASuperCharacterClass::Dash);

		EnhancedInputComponent->BindAction(ChargeShootAction, ETriggerEvent::Completed, this,
		                                   &ASuperCharacterClass::ChargedShoot);

		EnhancedInputComponent->BindAction(ChargeShootAction, ETriggerEvent::Started, this,
										   &ASuperCharacterClass::StartShootCharge);
		
		EnhancedInputComponent->BindAction(ChargeShootAction, ETriggerEvent::Canceled, this,
								   &ASuperCharacterClass::CancelCharge);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &ASuperCharacterClass::Shoot);
	}
}

void ASuperCharacterClass::CancelCharge()
{
	SpawnedChargeProjectile->Destroy();
}

void ASuperCharacterClass::Look(const FInputActionValue& Value)
{
	if (IsDead)
		return;

	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y*MouseSensitivity);
	AddControllerYawInput(LookAxisVector.X*MouseSensitivity);
}

void ASuperCharacterClass::Move(const FInputActionValue& Value)
{
	if (IsDead)
		return;

	const FVector2D MovementVector = Value.Get<FVector2D>();

	MovementVector3D = FVector(MovementVector.X, MovementVector.Y, 0);
	// UE_LOG(LogTemp,Warning,TEXT("%f,%f"),MovementVector.X,MovementVector.Y);
	if (PC && bCanMove)
	{
		const FRotator Rotation = PC->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0.f);

		ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y);

		RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASuperCharacterClass::ChargedShoot(const FInputActionValue& Value)
{
	if (IsDead)
		return;

	SpawnedChargeProjectile->NiagaraComponent->SetNiagaraVariableBool("beenShot",true);
	SpawnedChargeProjectile->SetActorRotation(CameraComp->GetForwardVector().Rotation());
	SpawnedChargeProjectile->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SpawnedChargeProjectile->bIsShot = true;
	
}

void ASuperCharacterClass::Shoot(const FInputActionValue& Value)
{
	if (IsDead)
		return;

	if (bShootOnCooldown)
	{
		return;
	}

	GetWorld()->SpawnActor<ASuperProjectileClass>(StandardProjectile,GetActorLocation(),CameraComp->GetForwardVector().Rotation());
}

void ASuperCharacterClass::StartShootCharge()
{
	SpawnedChargeProjectile = GetWorld()->SpawnActor<ASuperProjectileClass>(ChargedProjectile,FVector(150,80,0),CameraComp->GetForwardVector().Rotation());
	SpawnedChargeProjectile->AttachToComponent(CameraComp,FAttachmentTransformRules::KeepRelativeTransform);
	SpawnedChargeProjectile->bIsShot = false;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ASuperCharacterClass::FullCharged,2,false);
}

void ASuperCharacterClass::FullCharged()
{
	SpawnedChargeProjectile->NiagaraComponent->SetNiagaraVariableBool("Bool_VortexForce",true);
	SpawnedChargeProjectile->NiagaraComponent->SetNiagaraVariableBool("Bool_Color",false);
}

void ASuperCharacterClass::ChargingShootEffect()
{
}

void ASuperCharacterClass::Dash(const FInputActionValue& Value)
{
	if (IsDead)
		return;

	if (Value.Get<bool>() && !bIsDashing && !bDashIsOnCooldown)
	{
		DashStartLocation = GetActorLocation();
		DashEndLocation = GetActorLocation() + (ForwardDirection * MovementVector3D.Y + RightDirection * MovementVector3D.X) * DashDistance;
		bIsDashing = true;
		DashStartTime = GetWorld()->GetTimeSeconds();
		FVector StandingFloorNormal = GetCharacterMovement()->CurrentFloor.HitResult.Normal;
		FVector DashDirection = (ForwardDirection * MovementVector3D.Y + RightDirection * MovementVector3D.X);
		if(!StandingFloorNormal.Equals(GetActorUpVector()) && !GetCharacterMovement()->IsFalling())
		{
			FVector CrossVector = FVector::CrossProduct(StandingFloorNormal, -DashDirection);
			FRotator Rotation = UKismetMathLibrary::RotatorFromAxisAndAngle(CrossVector,90 - StandingFloorNormal.Rotation().Pitch);
			FVector CrossCrossVector = FVector::CrossProduct(StandingFloorNormal,CrossVector.GetSafeNormal());
			CrossCrossVector.Z += 0.1;
			DashEndLocation = GetActorLocation() + CrossCrossVector.GetSafeNormal() * DashDistance;
		}
	}
}

void ASuperCharacterClass::DashInterpolation(float DeltaTime)
{
	if (bIsDashing)
	{
		float ElapsedTime = GetWorld()->GetTimeSeconds() - DashStartTime;
		float Alpha = FMath::Clamp(ElapsedTime / DashDuration, 0.f, 1.f);
		SetActorLocation(FMath::Lerp(DashStartLocation,
		                             DashEndLocation,
		                             Alpha), true);
		//GetActorForwardVector().GetSafeNormal()
		if (Alpha >= 1.0f)
		{
			bDashIsOnCooldown = true;
			bIsDashing = false;
			GetMovementComponent()->Velocity = FVector::Zero();
		}
	}
}


float ASuperCharacterClass::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                       AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0)
	{
		UGameplayStatics::GetGameMode(GetWorld());
	}

	return 0;
}


void ASuperCharacterClass::LoadGame()
{
	if (Boss == nullptr)
	{
		return;
	}

	SaveGameClass = Cast<USaveGameClass>(UGameplayStatics::LoadGameFromSlot("MySaveSlot", 0));
	SetActorLocation(SaveGameClass->PlayerLocation);
	Boss->CurrentHealt = SaveGameClass->BossCurrentHealth;
	Boss->SetActorLocation(SaveGameClass->BossLocation);
	Boss->bIsCharging = false;
}

void ASuperCharacterClass::Jump()
{
	if (IsDead)
		return;

	Super::Jump();
}

void ASuperCharacterClass::ToggleHit()
{
	HasShotHit = true;

	FTimerHandle Timerhandle;
	GetWorldTimerManager().SetTimer(
		Timerhandle, this, &ASuperCharacterClass::ResetHit, 0.1f);
}

void ASuperCharacterClass::ResetHit()
{
	HasShotHit = false;
}

void ASuperCharacterClass::CooldownsHandler(float DeltaTime)
{
	if (bRechargeStamina && CurrentStamina < MaxStamina)
	{
		CurrentStamina += DeltaTime * StaminaRegen;
	}

	if (bDashIsOnCooldown)
	{
		DashCurrentCooldown -= DeltaTime;
	}

	if (DashCurrentCooldown < 0.0f)
	{
		bDashIsOnCooldown = false;
		DashCurrentCooldown = DashMaxCooldown;
	}

	if (bShootOnCooldown)
	{
		CurrentShootCooldown -= DeltaTime;
	}

	if (CurrentShootCooldown <= 0)
	{
		CurrentShootCooldown = MaxShootCooldown;
		bShootOnCooldown = false;
	}
}

void ASuperCharacterClass::Respawn()
{
	IsDead = true;

	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle, this, &ASuperCharacterClass::RespawnTimer, 1.f);
}

void ASuperCharacterClass::RespawnTimer()
{
	UGameplayStatics::OpenLevel(GetWorld(), *UGameplayStatics::GetCurrentLevelName(GetWorld()), true);
}
