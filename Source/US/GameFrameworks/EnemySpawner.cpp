#include "EnemySpawner.h"

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