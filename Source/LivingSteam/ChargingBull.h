// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChargingBull.generated.h"

UCLASS()
class LIVINGSTEAM_API AChargingBull : public APawn
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
	bool ChargeAttack();

	void JumpAttack();

	void RotateBull();

	void CirclePlayer();


private:
	class ACharacter* PlayerRef;

	UPROPERTY(BlueprintReadWrite, meta =(AllowPrivateAccess="true"))
	FVector Target;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FHitResult ChargeTraceResult;
	UWorld* World;

	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess="true"))
	bool bIsCharging = false;

	bool bFoundPlayer = false;

};
