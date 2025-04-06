#include "GameFrameworks/ProjectileSubsystem.h"

#include "Weapons/USProjectile.h"
#include "Weapons/USProjectilePool.h"
#include "Weapons/Datas/ProjectileDataAsset.h"

void UProjectileSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UProjectileSubsystem::TryRegisterProjectileInPool(const UProjectileDataAsset* ProjectileDataAsset)
{
    if (!IsValid(ProjectileDataAsset)) return;

    if (PoolMap.Contains(ProjectileDataAsset)) return;

    AUSProjectilePool* Pool = GetWorld()->SpawnActor<AUSProjectilePool>(AUSProjectilePool::StaticClass());
    Pool->Init(ProjectileDataAsset);

    PoolMap.Add(ProjectileDataAsset, Pool);
}

AUSProjectile* UProjectileSubsystem::GetAvailableProjectile(UProjectileDataAsset* ProjectileDataAsset)
{
    if (!IsValid(ProjectileDataAsset)) return nullptr;

    AUSProjectilePool* ProjectilePool = *(PoolMap.Find(ProjectileDataAsset));
    if (!IsValid(ProjectilePool)) return nullptr;

    return ProjectilePool->GetAvailableProjectile();
}