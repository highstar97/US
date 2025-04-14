#include "RoundStarter.h"

#include "DataValidator.h"
#include "GameModes/USGameMode.h"
#include "Characters/USHeroCharacter.h"

#include "Components/BoxComponent.h"

ARoundStarter::ARoundStarter()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	SetRootComponent(MeshComponent);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	TriggerBox->SetupAttachment(RootComponent);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionObjectType(ECC_WorldStatic);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);
	TriggerBox->SetBoxExtent(FVector(100.0f));
	TriggerBox->SetGenerateOverlapEvents(true);
}

void ARoundStarter::BeginPlay()
{
	Super::BeginPlay(); 
	
	if (!IsValid(TriggerBox)) return;

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ARoundStarter::OnTriggerBoxBeginOverlap);

	if(!IS_VALID_OR_WARN(MeshComponent->GetStaticMesh(), FString::Printf(TEXT("%s의 BP에 StaticMesh가 할당되지 않음."), *GetActorLabel()))) return;
}

void ARoundStarter::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !Cast<AUSHeroCharacter>(OtherActor)) return;

	NotifyGameModeToStartRound();
}

void ARoundStarter::NotifyGameModeToStartRound()
{
	AUSGameMode* GameMode = Cast<AUSGameMode>(GetWorld()->GetAuthGameMode());
	if (!IsValid(GameMode)) return;

	GameMode->StartRound();
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}