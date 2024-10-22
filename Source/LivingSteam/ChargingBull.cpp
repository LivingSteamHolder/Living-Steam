// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargingBull.h"

#include "Boulder.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "SuperCharacterClass.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "SaveGameClass.h"
#include "SlowActorEffect.h"
#include "Components/StaticMeshComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"


// Sets default values
AChargingBull::AChargingBull()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100;
	CurrentHealt = MaxHealth;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	BodyMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AChargingBull::BeginPlay()
{
	Super::BeginPlay();
	PlayerRef = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	World = GetWorld();
	bIsCharging = false;
	bVulnerable = false;
	CurrentHealt = MaxHealth;
	VulnerableHealth = MaxHealth-21;
	BullStartPosition = GetActorLocation();
	PillarsDestroyed = 0.f;
	SlowComponent = FindComponentByClass<USlowActorEffect>();
	if(SlowComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("SLOW EFFECT FOUND"))
		SlowComponent->DefaultInterpSpeed = BullChargeSpeedInterp;
	}
}

// Called every frame
void AChargingBull::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentHealt);
	//UE_LOG(LogTemp, Warning, TEXT("%f, %f"), Target.X, Target.Y)

	if (!bIsCharging)
	{
		RotateBull();
		IsRotating = true;
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

//Checks if bull can charge towards player and if so sets target chargelocation
bool AChargingBull::ChargeAttack(float BoxSize)
{
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(OuterWall);
	FCollisionShape Box = FCollisionShape::MakeBox(FVector(10, 10, 250));


	bool BHit = World->SweepSingleByChannel(ChargeTraceResult, GetActorLocation() + GetActorForwardVector() * 350,
	                                        GetActorLocation() + GetActorForwardVector() * 100000,
	                                        FQuat::Identity, ECC_GameTraceChannel2,
	                                        Box, params);

	if (BHit && Cast<ASuperCharacterClass>(ChargeTraceResult.GetActor()))
	{
		bIsCharging = true;
		FHitResult ExtraTrace;
		bool BExtraHit = World->SweepSingleByChannel(ExtraTrace, GetActorLocation() + GetActorForwardVector() * 350,
		                                             ChargeTraceResult.GetActor()->GetActorLocation() +
		                                             GetActorForwardVector() * 1500,
		                                             FQuat::Identity, ECC_GameTraceChannel3,
		                                             FCollisionShape::MakeBox(FVector(50.f, 50.f, 50.f)), params);
		if (BExtraHit)
		{
			Target = ExtraTrace.ImpactPoint - GetActorForwardVector() * 50;
		}
		else
		{
			Target = ChargeTraceResult.GetActor()->GetActorLocation() + GetActorForwardVector() * 1500;
		}
		Target.Z = GetActorLocation().Z;

		//GetWorld()->GetTimerManager().SetTimer(ChargeTimer, [this](){bIsCharging = true;}, 2.f, false );
		return true;
	}
	return false;
}

//Interpolates to target location wich is used for charge
void AChargingBull::ExecuteChargeInterpolation(float DeltaTime)
{
	IsPreparingToCharge = false;
	IsRotating = false;

	UE_LOG(LogTemp, Warning, TEXT("HEJ"))
	SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), Target, DeltaTime,SlowComponent->CurrentInterpSpeed), true);
	if (GetActorLocation().Equals(Target))
	{
		bIsCharging = false;
	}
}

//Rotates bull to always face the player
void AChargingBull::RotateBull()
{
	if (PlayerRef)
	{
		const FRotator& TargetRotation = (PlayerRef->GetActorLocation() - GetActorLocation()).Rotation();

		FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, World->GetDeltaSeconds(),
		                                                100);

		NewRotation.Pitch = 0;
		SetActorRotation(NewRotation);


		if (GetActorRotation().Yaw == TargetRotation.Yaw)
		{
			IsRotating = false;
			IsPreparingToCharge = true;
		}
		else
		{
			IsRotating = true;
			IsPreparingToCharge = false;
		}
	}
}

//Sets new conditions for phase 2
void AChargingBull::StartNextPhase()
{
	PhaseNumber = 2;
	Target = FVector(0,0,2000);
	bIsCharging=true;
	UBlackboardComponent* BBC = UAIBlueprintHelperLibrary::GetBlackboard(this);
	BBC->SetValueAsInt("PhaseKey", PhaseNumber);
}

void AChargingBull::SpawnShotEffect(float DamageAmount)
{
	TakeDamage(DamageAmount);
}

//Takes damage if vulnerable
void AChargingBull::TakeDamage(float DamageAmount)
{
	if (bVulnerable)
		this->CurrentHealt -= DamageAmount;
	if(CurrentHealt<0)
		UGameplayStatics::OpenLevel(this,"MainMenu");
	else if(CurrentHealt < VulnerableHealth)
	{
		bVulnerable = false;
		if(PillarsDestroyed==3)
			StartNextPhase();
		else
			VulnerableHealth -= 21;
	}
}

//Spawns a shockwave at actors location
void AChargingBull::ShockWaveAttack()
{
	const auto NewShard = GetWorld()->SpawnActor<AActor>(BPShockwave, GetActorLocation(), GetActorRotation());

	if (NewShard)
	{
		NewShard->SetOwner(this);
	}
}

void AChargingBull::SaveGame()
{
	if (!UGameplayStatics::DoesSaveGameExist("MySaveSlot", 0))
	{
		SaveGameClass = Cast<USaveGameClass>(UGameplayStatics::CreateSaveGameObject(USaveGameClass::StaticClass()));
		SaveGameClass->BossLocation = BullStartPosition;
		SaveGameClass->BossCurrentHealth = CurrentHealt;
		SaveGameClass->PlayerLocation = Cast<ASuperCharacterClass>(PlayerRef)->SpawnPoint;
		UGameplayStatics::SaveGameToSlot(SaveGameClass, "MySaveSlot", 0);
		UE_LOG(LogTemp, Warning, TEXT("GAME SAVED"));
	}
}

//Keeps count of destroyed pillars
void AChargingBull::AddDestroyedPillar()
{
	PillarsDestroyed += 1.f;
}
