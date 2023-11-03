// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SuperCharacterClass.generated.h"

UCLASS()
class LIVINGSTEAM_API ASuperCharacterClass : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASuperCharacterClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	//Variables
	
	
	//Character Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats")
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats")
	float MaxStamina = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats")
	float CurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats")
	float StaminaRegen = 1.f;
	UPROPERTY(EditAnywhere,Category="Base Stats")
	float MaxMovementSpeed = 600;
	UPROPERTY(EditAnywhere,Category="Base Stats")
	float RunningSpeedMultiplyer = 2;
	UPROPERTY(EditAnywhere,Category="Base Stats")
	bool bIsRunning = false;

	//Components

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UCharacterMovementComponent* CharacterMovement;
	
	//Camera
	UPROPERTY(EditAnywhere, Category="Camera")
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere,Category="Camera")
	class UCameraComponent* CameraComp;
	
	//Funktioner

	//Movement
	void MoveForward(const float Axis);
	void MoveRight(const float Axis);
	void Run();
	
	//PlayerState
	void TakeDamage(float DamageAmount);
	virtual void Attack();

};
