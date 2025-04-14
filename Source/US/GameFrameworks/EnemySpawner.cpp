#include "EnemySpawner.h"

#include "DataValidator.h"
#include "Characters/USEnemyCharacter.h"

#include "Components/StaticMeshComponent.h"

AEnemySpawner::AEnemySpawner()
{
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

	PrimaryActorTick.bCanEverTick = false;
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AUSEnemyCharacter> EnemyClass, FVector Location)
{
    if (!EnemyClass) return;

    FActorSpawnParameters Params;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    AUSEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AUSEnemyCharacter>(EnemyClass, Location, FRotator::ZeroRotator, Params);

    if (SpawnedEnemy)
    {
        UE_LOG(LogTemp, Log, TEXT("Spawned enemy %s at %s"), *SpawnedEnemy->GetName(), *Location.ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn enemy at %s"), *Location.ToString());
    }
}

void AEnemySpawner::BeginPlay()
{
    Super::BeginPlay();

    if (!IS_VALID_OR_WARN(MeshComponent->GetStaticMesh(), FString::Printf(TEXT("%s의 BP에 StaticMesh가 할당되지 않음."), *GetActorLabel()))) return;
}