// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShotActionInterface.h"
#include "GameFramework/Pawn.h"
#include "TitanHead.generated.h"

class ATitanHeadShield;

UCLASS()
class LIVINGSTEAM_API ATitanHead : public APawn, public IShotActionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATitanHead();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void TakeDamage(float AmountDamage);

	float GetHealth();

	void SpawnShotEffect(float DamageAmount = 0) override;

	float CurrentHealth;

private:
	//Variables

	UPROPERTY(EditAnywhere,Category="Shields")
	TArray<ATitanHeadShield*> TitanShieldArray;
	
	UPROPERTY(EditAnywhere)
	float MaxHeadHealth = 100;

	UPROPERTY(EditAnywhere)
	class ATitan* Titan;

	//Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* HeadMesh;

	//Functions
	void RotateShields();
};
