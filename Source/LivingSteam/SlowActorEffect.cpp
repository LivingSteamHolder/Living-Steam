// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowActorEffect.h"

#include "ChargingBull.h"

// Sets default values for this component's properties
USlowActorEffect::USlowActorEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void USlowActorEffect::BeginPlay()
{
	Super::BeginPlay();
	// ...
	CurrentInterpSpeed = DefaultInterpSpeed;
}


// Called every frame
void USlowActorEffect::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if(bIsSlowedDown && CurrentSlowDuration > 0)
	{
		CurrentSlowDuration -= DeltaTime;
	}
	else
	{
		CurrentSlowDuration = SlowDuration;
		bIsSlowedDown = false;
		CurrentInterpSpeed = DefaultInterpSpeed;
	}
	// ...
}

