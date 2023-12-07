// Fill out your copyright notice in the Description page of Project Settings.


#include "StandardProjectile.h"

#include "Components/SphereComponent.h"

void AStandardProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereHitBox->OnComponentHit.AddDynamic(this,&AStandardProjectile::OnHit);
}

void AStandardProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AStandardProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector normalImpulse, const FHitResult& Hit)
{
	Super::OnHit(HitComponent, OtherActor, OtherComp, normalImpulse, Hit);
}
