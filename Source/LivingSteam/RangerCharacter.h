// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SuperCharacterClass.h"
#include "RangerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LIVINGSTEAM_API ARangerCharacter : public ASuperCharacterClass
{
	GENERATED_BODY()
public:
	ARangerCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Combat
	virtual void Attack() override;
private:
	//Variables
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* DashAction;
	
	//Movement
	void Dash(const FInputActionValue& Value);
};


