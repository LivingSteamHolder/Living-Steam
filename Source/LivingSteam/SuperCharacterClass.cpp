// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperCharacterClass.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ASuperCharacterClass::ASuperCharacterClass()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SpringArm Component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 700;
	SpringArmComp->SocketOffset = FVector(0,0,600);
	SpringArmComp->SetRelativeRotation(FRotator(0,45,0));

	//Camera Component
	CameraComp = CreateDefaultSubobject<UCameraComponent>("PlayerCamera");
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->SetRelativeRotation(FRotator(-30,0,0));
	//Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("PlayerMesh");
	MeshComp->SetupAttachment(RootComponent);
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
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
	
	UGameplayStatics::GetPlayerController(this,0)->SetShowMouseCursor(true);

}

// Called every frame
void ASuperCharacterClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStamina<MaxStamina && bIsRunning == false)
	{
		CurrentStamina+=DeltaTime*StaminaRegen;
	}
	if (bIsRunning==true && CurrentStamina>=0)
	{
		CurrentStamina-=DeltaTime;
	}
}

// Called to bind functionality to input
void ASuperCharacterClass::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Bind Axis
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASuperCharacterClass::Move);
	}
	//PlayerInputComponent->BindAxis("MoveForward",this,&ASuperCharacterClass::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight",this,&ASuperCharacterClass::MoveRight);

	//Bind Action
	PlayerInputComponent->BindAction("Run",IE_Pressed,this, &ASuperCharacterClass::Run);
	PlayerInputComponent->BindAction("Run",IE_Released,this,&ASuperCharacterClass::Run);
	PlayerInputComponent->BindAction("Attack",IE_Pressed,this,&ASuperCharacterClass::Attack);
}

void ASuperCharacterClass::MoveForward(const float Axis)
{
	const FRotator Rotation = PC->GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw + 45,0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection * Axis);
}

void ASuperCharacterClass::MoveRight(const float Axis)
{
	const FRotator Rotation = PC->GetControlRotation();
	const FRotator YawRotation(0,Rotation.Yaw + 45,0.f);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput((RightDirection * Axis));
}

void ASuperCharacterClass::Run()
{

	CharacterMovement = GetCharacterMovement();
	if(CharacterMovement->MaxWalkSpeed == MaxMovementSpeed)
	{
		CharacterMovement->MaxWalkSpeed *= RunningSpeedMultiplyer;
		bIsRunning = true;
	}
	else
	{
		CharacterMovement->MaxWalkSpeed = MaxMovementSpeed;
		bIsRunning = false;
	}
}

void ASuperCharacterClass::LookAtMouse(int ControllIndex)
{
	FVector2D MousePosition;
	UGameplayStatics::GetPlayerController(this, ControllIndex)->GetMousePosition(MousePosition.X, MousePosition.Y);
	FVector2D CharacterScreenPosition;
	UGameplayStatics::ProjectWorldToScreen(UGameplayStatics::GetPlayerController(this,0), GetActorLocation(), CharacterScreenPosition);
	FVector2D ScreenOffset = MousePosition - CharacterScreenPosition;
	float DesiredYaw = FMath::RadiansToDegrees(FMath::Atan2(ScreenOffset.Y, ScreenOffset.X));
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = DesiredYaw;
	SetActorRotation(NewRotation);

}

void ASuperCharacterClass::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if(PC)
	{
		const FRotator Rotation = PC->GetControlRotation();
		const FRotator YawRotation(0,Rotation.Yaw + 45,0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection,MovementVector.Y);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection,MovementVector.X);
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

void ASuperCharacterClass::Attack()
{
	//Do nothing
}







