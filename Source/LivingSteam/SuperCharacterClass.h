// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "SuperCharacterClass.generated.h"

class UInputAction;
class ASuperProjectileClass;
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

	void CancelCharge();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DashCurrentCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float DashMaxCooldown = 0.5;

	UPROPERTY(BlueprintReadWrite)
	FVector SpawnPoint;

	UFUNCTION(BlueprintCallable)
	void Respawn();

	// Shahin
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector StartLocation;

	UFUNCTION(BlueprintCallable)
	void ResetLocation();

private:
	UFUNCTION(BlueprintCallable)
	void WriteSensitivityToFile(const float sens)
	{
		FFileHelper::SaveStringToFile(FString("sensitivity=") + FString::SanitizeFloat(sens), *(FPaths::ProjectDir() + "test.txt"));
	}

	UFUNCTION(BlueprintCallable)
	float GetSensitivityFromFile()
	{
		FString Result;
		
		FFileHelper::LoadFileToString(Result, *(FPaths::ProjectDir() + "test.txt"));

		FString Left, Right;
		Result.Split(TEXT("="), &Left, &Right);
		
		return FCString::Atof(*Right);
	}
	
	//Components
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category="Input")
	class UInputMappingContext* PlayerMapping;

	//Character Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float MaxHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float MaxStamina = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float CurrentStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float StaminaRegen = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float MaxMovementSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Base Stats", meta=(AllowPrivateAccess))
	float RunningSpeedMultiplyer = 2;

	//InputAction
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* DashAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ChargeShootAction;
	bool bRechargeStamina = true;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Dash", meta=(AllowPrivateAccess="true"))
	class AActor* CurrentTitan;

	//Shoot Variables
	UPROPERTY(EditAnywhere, Category="Shoot Stats")
	float ShootCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shoot Stats", meta=(AllowPrivateAccess))
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shoot Stats", meta=(AllowPrivateAccess))
	float ChargeDamage;

	//Dash Variables
	UPROPERTY(EditAnywhere, Category="Dash")
	float DashStartTime;

	FVector DashEndLocation;
	FVector DashStartLocation;
	FVector ForwardDirection;
	FVector RightDirection;

	UPROPERTY(EditAnywhere, Category="Dash")
	float DashDistance = 20;

	UPROPERTY(EditAnywhere, Category="Dash")
	float DashDuration = 0.5;

	bool bIsDashing;

	bool bDashIsOnCooldown;

	float CurrentDashDuration;

	bool bCanMove = true;

	FVector MovementVector3D;
	//Player Controller
	APlayerController* PC;

	//Shoot Variables
	FHitResult HitTarget;

	UCharacterMovementComponent* CharacterMovement;

	//Camera
	UPROPERTY(EditAnywhere, Category="Camera", meta = (AllowPrivateAccess))
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, Category="Camera", BlueprintReadOnly, meta = (AllowPrivateAccess))
	class UCameraComponent* CameraComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess))
	float MouseSensitivity = 1.f;

	//Niagara
	UPROPERTY(EditAnywhere, Category="Effects")
	UNiagaraSystem* ShootChargeEffect;

	UPROPERTY(EditAnywhere)
	USceneComponent* EffectLocation;

	UNiagaraComponent* NiagaraComp;

	UPROPERTY(EditAnywhere,Category="Projectile",meta = (AllowPrivateAccess))
	TSubclassOf<ASuperProjectileClass> ChargedProjectile;

	UPROPERTY(EditAnywhere,Category="Projectile",meta = (AllowPrivateAccess))
	TSubclassOf<ASuperProjectileClass> StandardProjectile;
	
	//Functions
	//Movement
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Run(const FInputActionValue& Value);

	//Shoot
	void ChargedShoot(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);

	void StartShootCharge();
	void ChargingShootEffect();

	//Dash Function
	void Dash(const FInputActionValue& Value);
	void DashInterpolation(float DeltaTime);

	//PlayerState
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	UPROPERTY(EditAnywhere)
	class AChargingBull* Boss;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	;
	bool bShootOnCooldown;

	UPROPERTY(EditAnywhere)
	float MaxShootCooldown = 0.5;

	float CurrentShootCooldown;

	class USaveGameClass* SaveGameClass;

	ASuperProjectileClass* SpawnedChargeProjectile;

	FTimerHandle TimerHandle;

	void FullCharged();

	void ChargingShot();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	// Shahin
	void Jump() override;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool IsDead = false;

	void ToggleHit();
	void ResetHit();

	void CooldownsHandler(float DeltaTime);

	void RespawnTimer();

	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool HasShotHit = false;
};
