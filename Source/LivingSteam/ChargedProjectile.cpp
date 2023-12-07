// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargedProjectile.h"

#include "ChargingBull.h"
#include "Elevator.h"
#include "NiagaraFunctionLibrary.h"
#include "SlowActorEffect.h"
#include "Components/SphereComponent.h"

void AChargedProjectile::BeginPlay()
{
	Super::BeginPlay();
	bIsShot = false;
	SphereHitBox->OnComponentHit.AddDynamic(this,&AChargedProjectile::OnHit);
}

void AChargedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AChargedProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector normalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp,Warning,TEXT("HIT HIT %s"),*OtherActor->GetName());
	if(USlowActorEffect* SlowActorEffect = OtherActor->FindComponentByClass<USlowActorEffect>())
	{
		UE_LOG(LogTemp,Warning,TEXT("FOUND SLOW ON BULL"));
		if(SlowActorEffect->CurrentInterpSpeed >= SlowActorEffect->DefaultInterpSpeed/SlowActorEffect->AmountSlowValueDivision)
		{
			SlowActorEffect->CurrentInterpSpeed /= SlowActorEffect->AmountSlowValueDivision;
			SlowActorEffect->bIsSlowedDown = true;
		}
	}
	
	Super::OnHit(HitComponent, OtherActor, OtherComp, normalImpulse, Hit);
}


