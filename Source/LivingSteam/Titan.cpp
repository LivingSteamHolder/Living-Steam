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

	for(ATitanHead* TitanHead : HeadsArray)
	{
		MaxHealth += TitanHead->GetHealth();
	}
}

// Called every frame
void ATitan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATitan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

