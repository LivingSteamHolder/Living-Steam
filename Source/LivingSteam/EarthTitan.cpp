// Fill out your copyright notice in the Description page of Project Settings.


#include "EarthTitan.h"

#include "ThrowableShard.h"
#include "Kismet/GameplayStatics.h"


void AEarthTitan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation()
}

void AEarthTitan::ThrowRock()
{
	const auto NewShard = GetWorld()->SpawnActor<AThrowableShard>(BPThrowableShard, SpawnOffset * GetActorForwardVector() + GetActorLocation(), GetActorRotation());

	if (NewShard)
	{
		NewShard->SetOwner(this);
	}
}

void AEarthTitan::SpawnBoulder()
{
}
