// Fill out your copyright notice in the Description page of Project Settings.


#include "RangerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	bool bIsDashing = Value.Get<bool>();

	if(bIsDashing)
	{
		//GetCharacterMovement()->Velocity = FVector() * 200;
	}
	
	UE_LOG(LogTemp,Warning,TEXT("DASHING"));
	UE_LOG(LogTemp,Warning,TEXT("%f,%f"));
}

