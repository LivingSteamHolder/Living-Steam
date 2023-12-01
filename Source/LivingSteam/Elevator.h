// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

class UArrowComponent;

UCLASS()
class LIVINGSTEAM_API AElevator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AElevator();

	UFUNCTION(BlueprintCallable)
	void CallElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UArrowComponent* StartLocation = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UArrowComponent* EndLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float ElevatorSpeed = 5.f;

	bool IsGoingDown = false;
	bool IsActive = false;
};
