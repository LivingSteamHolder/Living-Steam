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
	ChargeAttack();

	if(!bIsCharging)
	{
		RotateBull();
		CirclePlayer();
	}

}

// Called to bind functionality to input
void AChargingBull::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AChargingBull::ChargeAttack(float BoxSize)
{

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(BoxSize, BoxSize, 250));


	bool BHit = World->SweepSingleByChannel(ChargeTraceResult, GetActorLocation()+GetActorForwardVector()*280, GetActorLocation()+GetActorForwardVector() * 100000,
											FQuat::Identity, ECC_GameTraceChannel2,
											Box, params);
	UE_LOG(LogTemp, Warning, TEXT("Target: %f, %f"), Target.X, Target.Y);

	if(BHit && Cast<ASuperCharacterClass>(ChargeTraceResult.GetActor()))
	{
		DrawDebugBox(GetWorld(), ChargeTraceResult.Location, Box.GetExtent(), FQuat::Identity, FColor::Purple, false);

		Target = ChargeTraceResult.GetActor()->GetActorLocation();

	}
	return BHit;
}

void AChargingBull::JumpAttack()
{
	
}

void AChargingBull::RotateBull()
{
	if(PlayerRef)
	{
	FRotator rot = (PlayerRef->GetActorLocation()-GetActorLocation()).Rotation();
	rot.Pitch = 0;
	SetActorRotation(rot);
		
	}
}

void AChargingBull::CirclePlayer()
{

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(250, 250, 250));
	FHitResult FHit;

	bool BHit = World->SweepSingleByChannel(FHit, GetActorLocation()+FVector(0,0,80), GetActorLocation()+FVector(0,0,80)+ GetActorRightVector() * 400* CircleDirection,
											FQuat::Identity, ECC_GameTraceChannel2,
											Box, params);



	if(BHit)
	{
		DrawDebugBox(GetWorld(), ChargeTraceResult.Location, Box.GetExtent(), FQuat::Identity, FColor::Purple, false);
		CircleDirection*=-1;
	}
	

	bFoundPlayer = (ChargeTraceResult.GetActor()!=PlayerRef);

	if(bFoundPlayer)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"),ChargeTraceResult.GetActor()!=PlayerRef ? TEXT("TRUE"):TEXT("FALSE"));
	FVector TangentVec = (FVector::CrossProduct(FVector(0,0,1), PlayerRef->GetActorLocation()-GetActorLocation())).GetSafeNormal();
	SetActorLocation(GetActorLocation()+TangentVec*CircleDirection*20);
	}
	ChargeAttack(50.f);
	if((ChargeTraceResult.ImpactPoint-GetActorLocation()).Length()< 100)
		SetActorLocation(GetActorLocation()+GetActorForwardVector()*10);

}

FVector AChargingBull::ExtraCharge()
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(150, 150, 50));
	FHitResult FHit;

	bool BHit = World->SweepSingleByChannel(FHit, GetActorLocation()+FVector(0,0,80), GetActorLocation()+FVector(0,0,80)+ GetActorForwardVector() * 500,
											FQuat::Identity, ECC_GameTraceChannel3,
											Box, params);

	if(BHit)
		return FHit.ImpactPoint;
	else
	{
		return GetActorLocation() + GetActorForwardVector()*800;
	}

	
}



