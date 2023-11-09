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
	virtual void Tick(float DeltaTime) override;

	void ThrowRock();
	void SpawnBoulder();
private:

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess= "true"))
	float SpawnOffset = 100.f;

	class ACharacter;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Shard", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AThrowableShard> BPThrowableShard;
};
