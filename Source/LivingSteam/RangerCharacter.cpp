// Fill out your copyright notice in the Description page of Project Settings.


#include "RangerCharacter.h"
#include "EnhancedInputComponent.h"

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
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(DashAction,ETriggerEvent::Started,this,&ARangerCharacter::Dash);
	}
	
}

void ARangerCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Ranger Attacking"))
	//Attack
}

void ARangerCharacter::Dash(const FInputActionValue& Value)
{
	FVector2D DashVector = Value.Get<FVector2D>();

	if(PC)
	{
		const FRotator Rotation = PC->GetControlRotation();
		
	}
	
	UE_LOG(LogTemp,Warning,TEXT("DASHING"));
}

