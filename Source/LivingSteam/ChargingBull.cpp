// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingBull.h"

#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "SuperCharacterClass.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"


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
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(50, 50, 50));


	bool BHit = World->SweepSingleByChannel(ChargeTraceResult, GetActorLocation()+FVector(0,0,80), GetActorLocation()+ GetActorForwardVector() * 10000,
											FQuat::Identity, ECC_Visibility,
											Box, params);

	if(BHit && Cast<ASuperCharacterClass>(ChargeTraceResult.GetActor()))
	{
		DrawDebugBox(GetWorld(), ChargeTraceResult.Location, Box.GetExtent(), FQuat::Identity, FColor::Purple, true);
		Target = ChargeTraceResult.GetActor()->GetActorLocation();
	}

}

void AChargingBull::JumpAttack()
{
	
}

void AChargingBull::RotateBull()
{
	FRotator rot = (PlayerRef->GetActorLocation()-GetActorLocation()).Rotation();
	rot.Pitch = 0;
	SetActorRotation(rot);
}

