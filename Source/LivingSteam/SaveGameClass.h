// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveGameClass.generated.h"

/**
 * 
 */
UCLASS()
class LIVINGSTEAM_API USaveGameClass : public USaveGame
{
	GENERATED_BODY()

public:
	
	float BossCurrentHealth;
	UPROPERTY(EditAnywhere, Category="Boss")
	FVector BossLocation;
	UPROPERTY(EditAnywhere, Category="Player")
	FVector PlayerLocation;
};
