// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

#include "Components/ArrowComponent.h"

// Sets default values
AElevator::AElevator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneRoot");

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);

	StartLocation = CreateDefaultSubobject<UArrowComponent>("StartLocation");
	StartLocation->SetupAttachment(RootComponent);

	EndLocation = CreateDefaultSubobject<UArrowComponent>("EndLocation");
	EndLocation->SetupAttachment(RootComponent);
}

void AElevator::CallElevator()
{
	IsGoingDown = !IsGoingDown;
	IsActive = true;
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetWorldLocation(StartLocation->GetComponentLocation());
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsActive)
		return;

	const FVector TargetLocation = IsGoingDown
		                               ? EndLocation->GetComponentLocation()
		                               : StartLocation->GetComponentLocation();

	if (MeshComponent->GetComponentLocation() == TargetLocation)
	{
		IsActive = false;
		return;
	}

	MeshComponent->SetWorldLocation(FMath::VInterpTo(MeshComponent->GetComponentLocation(), TargetLocation, DeltaTime,
	                                                 ElevatorSpeed));
}
