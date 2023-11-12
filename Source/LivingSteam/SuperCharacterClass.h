// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "SuperCharacterClass.generated.h"

class UInputAction;
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

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float DashCurrentCooldown;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float DashMaxCooldown = 0.5;
private:
	//Variables
	bool bRechargeStamina = true;

	bool bCanMove = true;

	UPROPERTY(BlueprintReadWrite, meta =(AllowPrivateAccess ="true"))
	FVector SpawnPoint;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Dash", meta=(AllowPrivateAccess="true"))
	class ATitan* CurrentTitan;
	
	//Dash Variables
	UPROPERTY(EditAnywhere,Category="Dash")
	float DashStartTime;


	
	bool bIsDashing;

	bool bDashIsOnCooldown;


	UPROPERTY(EditAnywhere,Category="Dash")
	float DashDuration = 0.5;

	float CurrentDashDuration;

	UPROPERTY(EditAnywhere,Category="Dash")
	float DashDistance = 20;
	
	FVector2D DashDirection;
	
	UPROPERTY(EditAnywhere,Category="Input")
	class UInputMappingContext* PlayerMapping;

	//InputAction
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* ShootAction;

	//Player Controller
	APlayerController* PC;

	//Shoot Variables
	FHitResult HitTarget;
	
	//Character Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float MaxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float MaxStamina = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float CurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float StaminaRegen = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float MaxMovementSpeed = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats",meta=(AllowPrivateAccess))
	float RunningSpeedMultiplyer = 2;
	
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
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);

	//Shoot
	void Shoot(const FInputActionValue& Value);

	//Niagara
	UPROPERTY(EditAnywhere,Category="Effects")
	UNiagaraSystem* ShootChargeEffect;

	UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere)
	USceneComponent* EffectLocation;

	void StartShootChargeEffect();
	void EndShootChargeEffect();

	//Dash Function
	void Dash(const FInputActionValue& Value);
	void DashInterpolation(float DeltaTime);
	//PlayerState
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Attack();

};
