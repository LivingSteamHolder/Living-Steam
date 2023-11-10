// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanHead.h"
#include "TitanHeadShield.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATitanHead::ATitanHead()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HeadMesh = CreateDefaultSubobject<UStaticMeshComponent>("HeadMesh");
	HeadMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATitanHead::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHeadHealth;
}

// Called every frame
void ATitanHead::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateShields();
}

// Called to bind functionality to input
void ATitanHead::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATitanHead::TakeDamage(float DamageAmount)
{
	UE_LOG(LogTemp,Warning,TEXT("%f"),DamageAmount);
	CurrentHealth -= DamageAmount;
	if(CurrentHealth <= 0 )
	{
		for(ATitanHeadShield* TitanShield : TitanShieldArray)
		{
			TitanShield->Destroy();
		}
		Destroy();
	}
}

float ATitanHead::GetHealth()
{
	return CurrentHealth;
}

void ATitanHead::SpawnShotEffect(float DamageAmount)
{
	TakeDamage(DamageAmount);
	UE_LOG(LogTemp,Warning,TEXT("HEAD HIT"));
	//Spawn Particle effect
}

void ATitanHead::RotateShields()
{
	for(ATitanHeadShield* TitanShield : TitanShieldArray)
	{
		FVector RotateVector = UKismetMathLibrary::RotateAngleAxis(FVector(TitanShield->Radius,0,0),(TitanShield->CurrentRotation + TitanShield->StartingAngle),FVector(0,0,1));
		TitanShield->SetActorLocation(GetActorLocation() + RotateVector);
	}
}

