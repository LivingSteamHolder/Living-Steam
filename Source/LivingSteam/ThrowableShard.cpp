// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableShard.h"

// Sets default values
AThrowableShard::AThrowableShard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrowableShard::BeginPlay()
{
	Super::BeginPlay();
	GetRootComponent()->ComponentVelocity=(Velocity* GetActorForwardVector());
	
}

// Called every frame
void AThrowableShard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

