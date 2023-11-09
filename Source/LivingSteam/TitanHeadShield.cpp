// Fill out your copyright notice in the Description page of Project Settings.


#include "TitanHeadShield.h"

#include "TitanHead.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATitanHeadShield::ATitanHeadShield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>("Shield Mesh");
	ShieldMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ATitanHeadShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATitanHeadShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentRotation += RotationSpeed;
}

void ATitanHeadShield::SpawnShotEffect(float DamageAmount)
{
	UE_LOG(LogTemp,Warning,TEXT("SHIELD HIT"));
	//Spawn Particle
}




