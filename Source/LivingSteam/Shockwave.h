#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shockwave.generated.h"

class USphereComponent;

UCLASS()
class LIVINGSTEAM_API AShockwave : public AActor
{
	GENERATED_BODY()
	
public:	
	AShockwave();

protected:
	virtual void BeginPlay() override;

	

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float Scale = 50.f; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float InterpSpeed = 50.f;
};
