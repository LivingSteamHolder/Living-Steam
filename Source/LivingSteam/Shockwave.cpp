#include "Shockwave.h"

#include "SuperCharacterClass.h"

AShockwave::AShockwave()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	MeshComponent->SetupAttachment(RootComponent);
	
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AShockwave::BeginPlay()
{
	Super::BeginPlay();
	
}

void AShockwave::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector& CurrentScale = GetActorScale();
	FVector TargetScale = FMath::VInterpConstantTo(CurrentScale, {Scale, Scale, Scale}, DeltaTime, InterpSpeed);
	UE_LOG(LogTemp, Warning, TEXT("%s"), *TargetScale.ToString());
	SetActorScale3D(TargetScale);

	if(CurrentScale == TargetScale){
		UE_LOG(LogTemp, Warning, TEXT("destroyed"));
		Destroy();
	}
}

void AShockwave::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const ASuperCharacterClass* Player = Cast<ASuperCharacterClass>(OtherActor);
	
	if (!Player)
		return;
	
	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActor(this);

	FHitResult HitResult;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), Player->GetActorLocation(), ECC_GameTraceChannel1, CollisionParameters);
	DrawDebugLine(GetWorld(), GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 10.f);
	
	if(!Hit || !Cast<ASuperCharacterClass>(HitResult.GetActor()))
		return;

	UE_LOG(LogTemp, Warning, TEXT("player"));
}

