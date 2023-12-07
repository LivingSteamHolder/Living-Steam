// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SlowActorEffect.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIVINGSTEAM_API USlowActorEffect : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USlowActorEffect();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float DefaultInterpSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentInterpSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float SlowDuration;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float AmountSlowValueDivision;
	
	bool bIsSlowedDown = false;

	float CurrentSlowTime;
	
	float CurrentSlowDuration;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
