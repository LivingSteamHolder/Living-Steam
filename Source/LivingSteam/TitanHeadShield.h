// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShotActionInterface.h"
#include "GameFramework/Actor.h"
#include "TitanHeadShield.generated.h"

UCLASS()
class LIVINGSTEAM_API ATitanHeadShield : public AActor, public IShotActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATitanHeadShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnShotEffect(float DamageAmount = 0) override;

	void RotateAroundPoint();

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	UPROPERTY(EditAnywhere)
	float StartingAngle;

	UPROPERTY(EditAnywhere)
	float Radius;

	float CurrentRotation;
private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ShieldMesh;
	
	UPROPERTY(EditAnywhere)
	class ATitanHead* TitanHead;
	
	FVector InitialLocation;

};
