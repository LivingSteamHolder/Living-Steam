// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingBull.h"

#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AChargingBull::AChargingBull()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChargingBull::BeginPlay()
{
	
	Super::BeginPlay();
	PlayerRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	World = GetWorld();
	
}

// Called every frame
void AChargingBull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotateBull();

}

// Called to bind functionality to input
void AChargingBull::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChargingBull::ChargeAttack()
{
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(100, 100, 100));


	bool BHit = World->SweepSingleByChannel(ChargeTraceResult, GetActorLocation(), GetActorForwardVector() * 1000,
											FQuat::Identity, ECC_Visibility,
											Box);

	if(BHit)
	{
		DrawDebugBox(GetWorld(), ChargeTraceResult.Location, Box.GetExtent(), FQuat(), FColor::Purple, true);
	}
}

void AChargingBull::RotateBull()
{
	SetActorRotation((PlayerRef->GetActorLocation()-GetActorLocation()).Rotation());
}

