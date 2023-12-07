// Fill out your copyright notice in the Description page of Project Settings.


#include "ChargedProjectile.h"

#include "SlowActorEffect.h"

void AChargedProjectile::BeginPlay()
{
	Super::BeginPlay();
	Super::bIsShot = false;
}

void AChargedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetActorLocation().ToString())
}

void AChargedProjectile::SetSlowDebuff()
{
	
}

void AChargedProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, normalImpulse, Hit);

	USlowActorEffect* SlowActorEffect = OtherActor->FindComponentByClass<USlowActorEffect>();
	if(SlowActorEffect)
	{
		SlowActorEffect->CurrentInterpSpeed /= SlowActorEffect->AmountSlowValueDivision;
		SlowActorEffect->bIsSlowedDown;
	}
}

