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
	bIsCharging = false;
	
}

// Called every frame
void AChargingBull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f"), Target.X, Target.Y)

	if (!bIsCharging)
	{
	RotateBull();
	}
	else
	{
		ExecuteChargeInterpolation(DeltaTime);
	}


		
}

// Called to bind functionality to input
void AChargingBull::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AChargingBull::ChargeAttack(float BoxSize)
{

	bIsCharging = true;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OuterWall);
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(10, 10, 250));


	bool BHit = World->SweepSingleByChannel(ChargeTraceResult, GetActorLocation()+GetActorForwardVector()*350, GetActorLocation()+GetActorForwardVector() * 100000,
											FQuat::Identity, ECC_GameTraceChannel2,
											Box, params);


	if(BHit && Cast<ASuperCharacterClass>(ChargeTraceResult.GetActor()))
	{
		FHitResult ExtraTrace;
		bool BExtraHit = World->SweepSingleByChannel(ExtraTrace, GetActorLocation()+GetActorForwardVector()*350, ChargeTraceResult.GetActor()->GetActorLocation()+GetActorForwardVector()*1500,
												FQuat::Identity, ECC_GameTraceChannel3,
												FCollisionShape::MakeBox(FVector(50.f,50.f,50.f)), params);
		if(BExtraHit)
		{
		Target = ExtraTrace.ImpactPoint;
		}
		else
		{
			Target = ChargeTraceResult.GetActor()->GetActorLocation()+GetActorForwardVector()*1500;
		}
		Target.Z = GetActorLocation().Z;
		
		//GetWorld()->GetTimerManager().SetTimer(ChargeTimer, [this](){bIsCharging = true;}, 2.f, false );
	}
	return BHit;

}

void AChargingBull::ExecuteChargeInterpolation(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("HEJ"))
	SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), Target, DeltaTime, 2000), true);
	if(GetActorLocation().Equals(Target))
	{

		bIsCharging = false;
	}
}




void AChargingBull::RotateBull()
{
	if(PlayerRef)
	{
		FRotator NewRotation =	FMath::RInterpConstantTo(GetActorRotation(),(PlayerRef->GetActorLocation()-GetActorLocation()).Rotation(), World->GetDeltaSeconds(), 100);

	NewRotation.Pitch = 0;
	SetActorRotation(NewRotation);
		
	}
}






