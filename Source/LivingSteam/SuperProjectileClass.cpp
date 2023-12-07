// Fill out your copyright notice in the Description page of Project Settings.


#include "SuperProjectileClass.h"

#include "Elevator.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "ShotActionInterface.h"

// Sets default values
ASuperProjectileClass::ASuperProjectileClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereHitBox = CreateDefaultSubobject<USphereComponent>("Hitbox");
	EffectLocation = CreateDefaultSubobject<USceneComponent>("EffectLocation");
	SphereHitBox->SetupAttachment(GetRootComponent());
	EffectLocation->SetupAttachment(GetRootComponent());
	
}

// Called when the game starts or when spawned
void ASuperProjectileClass::BeginPlay()
{
	Super::BeginPlay();
	NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(ShootChargeEffect,EffectLocation,NAME_None,EffectLocation->GetComponentLocation(),GetActorRightVector().Rotation(),EAttachLocation::Type::KeepWorldPosition,true);
}

// Called every frame
void ASuperProjectileClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsShot)
	MoveForward();

	EffectLocation->SetRelativeLocation(GetActorLocation());
}

void ASuperProjectileClass::MoveForward()
{
	SetActorLocation(GetActorLocation() + BulletSpeed * GetActorForwardVector().GetSafeNormal() * GetWorld()->GetDeltaSeconds(),true);

}

void ASuperProjectileClass::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector normalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("HIT"));
	IShotActionInterface* Interface = Cast<IShotActionInterface>(OtherActor);
	if (Interface)
	{
		Interface->SpawnShotEffect(Damage);
	}
	else
	{
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,DefaultImpactHitEffect,Hit.ImpactPoint,FRotator(0),FVector(1));
	}

	if(Hit.Component->ComponentTags.Contains("ElevatorLever"))
	{
		Cast<AElevator>(OtherActor)->CallElevator();
	}

	Destroy();
}



