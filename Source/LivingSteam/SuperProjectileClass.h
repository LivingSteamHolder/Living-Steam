// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SuperProjectileClass.generated.h"

UCLASS()
class LIVINGSTEAM_API ASuperProjectileClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASuperProjectileClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void MoveForward();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects",meta = (AllowPrivateAccess))
	class UNiagaraSystem* ShootChargeEffect;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= "Effects", meta = (AllowPrivateAccess))
	class UNiagaraSystem* DefaultImpactHitEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hitbox", meta = (AllowPrivateAccess))
	class USphereComponent* SphereHitBox;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Speed", meta = (AllowPrivateAccess))
	float BulletSpeed;

	UPROPERTY(EditAnywhere)
	USceneComponent* EffectLocation;

	UPROPERTY(EditAnywhere)
	float Damage;

	class UNiagaraComponent* NiagaraComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
