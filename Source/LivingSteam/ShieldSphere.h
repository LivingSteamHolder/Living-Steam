// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShotActionInterface.h"
#include "GameFramework/Actor.h"
#include "ShieldSphere.generated.h"

UCLASS()
class LIVINGSTEAM_API AShieldSphere : public AActor, public IShotActionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShieldSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnShotEffect(float DamageAmount = 0) override;

	void TakeDamage(float DamageAmount);
private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	float SphereHealth = 100;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bVulnerable = false;
};
