// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Titan.h"
#include "EarthTitan.generated.h"

class AThrowableShard;
/**
 * 
 */
UCLASS()
class LIVINGSTEAM_API AEarthTitan : public ATitan
{
	GENERATED_BODY()

public:
	void ThrowRock();
	void SpawnBoulder();
private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta =(AllowPrivateAccess = "true"))
	ALevelBounds* Shard;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess= "true"))
	float SpawnOffset;
	
};
