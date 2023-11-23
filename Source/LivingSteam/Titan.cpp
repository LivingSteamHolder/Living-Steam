// Fill out your copyright notice in the Description page of Project Settings.


#include "Titan.h"

// Sets default values
ATitan::ATitan()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATitan::BeginPlay()
{
	Super::BeginPlay();


	float HealthCounter = 0;
	for (ATitanHead* TitanHead : HeadsArray)
	{
		ensureMsgf(TitanHead != nullptr, TEXT("Titanhead is currently NULL"));

		HealthCounter += TitanHead->GetHealth();
	}
	MaxHealth = HealthCounter;
}

// Called every frame
void ATitan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Health = 0;
	for (ATitanHead* TitanHead : HeadsArray)
	{
		Health += TitanHead->GetHealth();
	}
	CurrentHealth = Health;
}

// Called to bind functionality to input
void ATitan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
