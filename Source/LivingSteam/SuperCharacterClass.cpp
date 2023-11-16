// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperCharacterClass.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
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
	SpringArmComp->SocketOffset = FVector(0,0,0);
	SpringArmComp->SetRelativeRotation(FRotator(0,0,0));

	//Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->SetRelativeRotation(FRotator(0,0,0));
	CameraComp->SetProjectionMode(ECameraProjectionMode::Perspective);
	
	//Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	MeshComp->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	EffectLocation = CreateDefaultSubobject<USceneComponent>("ShotChargeEffect");
	EffectLocation->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ASuperCharacterClass::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	CurrentStamina = MaxStamina;

	PC = Cast<APlayerController>(GetController());

	if(PC)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
		if(SubSystem)
		{
			SubSystem->AddMappingContext(PlayerMapping,0);
		}
		PC->SetControlRotation(GetActorRotation());
	}
	SpawnPoint = GetActorLocation();
}

// Called every frame
void ASuperCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bRechargeStamina && CurrentStamina < MaxStamina)
	{
		CurrentStamina+=DeltaTime*StaminaRegen;
	}

	if(bDashIsOnCooldown)
	{
		DashCurrentCooldown-= DeltaTime;
	}

	if(DashCurrentCooldown < 0.0f)
	{
		bDashIsOnCooldown = false;
		DashCurrentCooldown = DashMaxCooldown;
	}
	
	if(bIsDashing)
		DashInterpolation(DeltaTime);
	
	//UE_LOG(LogTemp,Warning,TEXT("%f,%f"),GetActorRotation().Pitch,GetActorRotation().Yaw);

}

// Called to bind functionality to input
void ASuperCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Bind Axis
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASuperCharacterClass::Move);
		
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ASuperCharacterClass::Look);
		
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ACharacter::Jump);
		
		EnhancedInputComponent->BindAction(DashAction,ETriggerEvent::Triggered,this,&ASuperCharacterClass::Dash);
		
		EnhancedInputComponent->BindAction(ChargeShootAction,ETriggerEvent::Completed,this,&ASuperCharacterClass::ChargedShoot);
		
		EnhancedInputComponent->BindAction(ShootAction,ETriggerEvent::Triggered,this,&ASuperCharacterClass::Shoot);
	}
}

void ASuperCharacterClass::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);

	if (NiagaraComp)
	{
		EffectLocation->SetRelativeRotation(CameraComp->GetForwardVector().Rotation());
	}
}

void ASuperCharacterClass::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if(PC && bCanMove)
	{
		const FRotator Rotation = PC->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw,0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection,MovementVector.Y);
		
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection,MovementVector.X);
	}
}

void ASuperCharacterClass::ChargedShoot(const FInputActionValue& Value)
{
	const FVector StartPosition = GetActorLocation();
	const FVector EndPosition = StartPosition + CameraComp->GetForwardVector() * 10000;
	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitTarget,StartPosition,EndPosition,ECC_WorldDynamic,QueryParam,FCollisionResponseParams());

	if(bHit)
	{
		//UE_LOG(LogTemp,Warning,TEXT("HIT"));
		IShotActionInterface* Interface = Cast<IShotActionInterface>(HitTarget.GetActor());
		if(Interface)
		{
			Interface->SpawnShotEffect(ChargeDamage);
		}
		else
		{
			//Spawn default debrie effect
		}
	}
}

void ASuperCharacterClass::Shoot(const FInputActionValue& Value)
{
	const FVector StartPosition = GetActorLocation();
	const FVector EndPosition = StartPosition + CameraComp->GetForwardVector() * 10000;
	FCollisionQueryParams QueryParam;
	QueryParam.AddIgnoredActor(this);
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitTarget,StartPosition,EndPosition,ECC_WorldDynamic,QueryParam,FCollisionResponseParams());

	if(bHit)
	{
		//UE_LOG(LogTemp,Warning,TEXT("HIT"));
		IShotActionInterface* Interface = Cast<IShotActionInterface>(HitTarget.GetActor());
		if(Interface)
		{
			Interface->SpawnShotEffect(Damage);
		}
		else
		{
			//Spawn default debrie effect
		}
	}

	DrawDebugLine(GetWorld(),StartPosition,EndPosition,FColor::Red,false,5,0,5);
}

void ASuperCharacterClass::Dash(const FInputActionValue& Value)
{
	if(Value.Get<bool>() && !bIsDashing && !bDashIsOnCooldown)
	{
		bIsDashing = true;
		DashStartTime = GetWorld()->GetTimeSeconds();
	}
}

void ASuperCharacterClass::DashInterpolation(float DeltaTime)
{
	if(bIsDashing)
	{
		float ElapsedTime = GetWorld()->GetTimeSeconds() - DashStartTime;
		float Alpha = FMath::Clamp(ElapsedTime/DashDuration,0.f,1.f);
		SetActorLocation(FMath::Lerp(GetActorLocation(),GetActorForwardVector().GetSafeNormal() * DashDistance + GetActorLocation(),Alpha),true);
		
		if(Alpha >= 1.0f)
		{
			bDashIsOnCooldown = true;
			bIsDashing = false;
		}
	}
}


float ASuperCharacterClass::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) 
{
	CurrentHealth-=DamageAmount;
	if(CurrentHealth<=0)
	{
		UGameplayStatics::GetGameMode(GetWorld());
	}

	return 0;
}





