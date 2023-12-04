// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperProjectileClass.h"
#include "ChargedProjectile.generated.h"

/**
 * 
 */
UCLASS()
class LIVINGSTEAM_API AChargedProjectile : public ASuperProjectileClass
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	
private:
	void SetSlowDebuff();

	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector normalImpulse, const FHitResult& Hit) override;
};