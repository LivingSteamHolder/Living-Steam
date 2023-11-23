#include "Shockwave.h"

#include "ChargingBull.h"
#include "SuperCharacterClass.h"
#include "Kismet/GameplayStatics.h"

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
	const FVector TargetScale = FMath::VInterpConstantTo(CurrentScale, {Scale, Scale, Scale}, DeltaTime, InterpSpeed);

	SetActorScale3D(TargetScale);

	if (CurrentScale == TargetScale)
		Destroy();
}

void AShockwave::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ASuperCharacterClass* Player = Cast<ASuperCharacterClass>(OtherActor);

	if (!Player)
		return;

	AActor* Bull = UGameplayStatics::GetActorOfClass(this, AChargingBull::StaticClass());

	ensureMsgf(Bull != nullptr, TEXT("Bull is NULL"));

	FCollisionQueryParams CollisionParameters;
	CollisionParameters.AddIgnoredActors(TArray<AActor*>({this, Bull}));

	FHitResult HitResult;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), Player->GetActorLocation(),
	                                                ECC_GameTraceChannel1, CollisionParameters);
	DrawDebugLine(GetWorld(), GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 10.f);
	DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 2.f, 10.f, FColor::Red, false, 10.f);

	if (!Hit || !Cast<ASuperCharacterClass>(HitResult.GetActor()))
		return;

	Player->Respawn();
}
