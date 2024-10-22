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
	StartLocation->SetArrowColor(FColor::Green);
	StartLocation->SetWorldRotation({-90.f, 0.f, 0.f});

	EndLocation = CreateDefaultSubobject<UArrowComponent>("EndLocation");
	EndLocation->SetupAttachment(RootComponent);
	EndLocation->SetWorldRotation({90.f, 0.f, 0.f});
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

	FVector Location = StartLocation->GetComponentLocation();

	Location.Z += 3000.f;

	MeshComponent->SetWorldLocation(Location);
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsActive)
		return;

	FVector TargetLocation = IsGoingDown
		                         ? EndLocation->GetComponentLocation()
		                         : StartLocation->GetComponentLocation();

	TargetLocation.Z += 3000.f;

	if (MeshComponent->GetComponentLocation() == TargetLocation)
	{
		IsActive = false;
		return;
	}

	MeshComponent->SetWorldLocation(FMath::VInterpConstantTo(MeshComponent->GetComponentLocation(), TargetLocation,
	                                                         DeltaTime,
	                                                         ElevatorSpeed));
}
