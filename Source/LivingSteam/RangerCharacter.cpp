// Fill out your copyright notice in the Description page of Project Settings.


#include "RangerCharacter.h"

ARangerCharacter::ARangerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ARangerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void ARangerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARangerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ARangerCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Ranger Attacking"))
	//Attack
}
