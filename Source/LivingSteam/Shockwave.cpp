// Fill out your copyright notice in the Description page of Project Settings.


#include "Shockwave.h"

// Sets default values
AShockwave::AShockwave()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShockwave::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShockwave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

