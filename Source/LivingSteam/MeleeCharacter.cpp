// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeCharacter.h"

AMeleeCharacter::AMeleeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


}

void AMeleeCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeleeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
