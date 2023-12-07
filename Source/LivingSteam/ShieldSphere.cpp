// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldSphere.h"

#include "ChargingBull.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShieldSphere::AShieldSphere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShieldSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShieldSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShieldSphere::SpawnShotEffect(float DamageAmount)
{
	TakeDamage(DamageAmount);
	//Spawn Particle effect
}

void AShieldSphere::TakeDamage(float DamageAmount)
{
		AChargingBull* Bull =Cast<AChargingBull>( UGameplayStatics::GetActorOfClass(this, AChargingBull::StaticClass()));
	if(Bull)
	{
		
	if (bVulnerable && !Bull->bVulnerable)
		SphereHealth-=DamageAmount;
	if (SphereHealth<=0)
	{
		Bull->bVulnerable=true;
		Bull->VulnerableHealth -= 21;
		Destroy();
	}
	}
	else
	{
		if (bVulnerable)
			SphereHealth-=DamageAmount;
	}

}


