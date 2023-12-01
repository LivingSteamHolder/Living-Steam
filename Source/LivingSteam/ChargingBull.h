// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShotActionInterface.h"
#include "GameFramework/Pawn.h"
#include "ChargingBull.generated.h"


UCLASS()
class LIVINGSTEAM_API AChargingBull : public APawn, public IShotActionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChargingBull();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	
	bool ChargeAttack(float BoxSize = 250.f);

	void ExecuteChargeInterpolation(float Deltatime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentHealt = 100.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float VulnerableHealth;
	
	void RotateBull();

	void StartNextPhase();



	void SpawnShotEffect(float DamageAmount = 0) override;

	void TakeDamage(float DamageAmount);
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsCharging = false;

	UPROPERTY(BlueprintReadWrite)
	bool bVulnerable;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccesss))
	UStaticMeshComponent* BodyMesh;

	class ACharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, meta =(AllowPrivateAccess="true"))
	FVector Target;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FHitResult ChargeTraceResult;

	FTimerHandle ChargeTimer;
	
	UWorld* World;

	UFUNCTION(BlueprintCallable)
	void ShockWaveAttack();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shard", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor> BPShockwave;
	
	bool bFoundPlayer = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess))
	int PhaseNumber = 1;
	
	float CircleDirection = 1;

	UPROPERTY(EditAnywhere)
	AActor* OuterWall;

	class USaveGameClass* SaveGameClass;

	FVector BullStartPosition;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess))
	float MaxHealth = 100.f;


	
	
	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void AddDestroyedPillar();
	// Shahin
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsPreparingToCharge = false;
	
	UPROPERTY(BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool IsRotating = false;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess))
	float PillarsDestroyed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,meta=(AllowPrivateAccess))
	TArray<AActor*> PillarArray;
};
