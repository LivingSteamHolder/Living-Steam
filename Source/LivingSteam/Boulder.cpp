// Fill out your copyright notice in the Description page of Project Settings.


#include "Boulder.h"

#include "SlowActorEffect.h"

// Sets default values
ABoulder::ABoulder()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>("RootComponent");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoulder::BeginPlay()
{
	Super::BeginPlay();

	SlowComponent = FindComponentByClass<USlowActorEffect>();
	if(SlowComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("SLOW EFFECT FOUND"));
	}
}

// Called every frame
void ABoulder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
