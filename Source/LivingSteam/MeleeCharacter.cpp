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
	PlayerInputComponent->BindAction("ShieldBlock",IE_Pressed,this, &AMeleeCharacter::ShieldBlock);
	PlayerInputComponent->BindAction("ShieldBlock",IE_Released,this,&AMeleeCharacter::ShieldBlock);
}

void AMeleeCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee Attacking"))
	//Attack
}

void AMeleeCharacter::ShieldBlock()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee Blocking"))
	//Use shield
}

