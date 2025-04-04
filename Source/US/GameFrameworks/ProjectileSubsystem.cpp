#include "GameFrameworks/ProjectileSubsystem.h"

#include "Weapons/USProjectile.h"
#include "Weapons/USProjectilePool.h"
#include "Weapons/Datas/ProjectileDataAsset.h"

void UProjectileSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
}

void UProjectileSubsystem::InitProjectilePools()
{
    for (TPair<UProjectileDataAsset*, AUSProjectilePool*>& ProjectilePool : ProjectilePools)
    {
        if (!IsValid(ProjectilePool.Key) || !IsValid(ProjectilePool.Value)) continue;

        ProjectilePool.Value->InitProjectiles(ProjectilePool.Key);
    }
}

AUSProjectile* UProjectileSubsystem::GetAvailableProjectile(UProjectileDataAsset* DataAsset)
{
    if (!IsValid(DataAsset)) return nullptr;

    AUSProjectilePool* ProjectilePool = *(ProjectilePools.Find(DataAsset));

    return ProjectilePool->GetAvailableProjectile();
}

void UProjectileSubsystem::RegistProjectilePool(UProjectileDataAsset* DataAsset, AUSProjectilePool* Pool)
{
    if (!IsValid(DataAsset)) return;

    if (!IsValid(Pool))
    {
        Pool = GetWorld()->SpawnActor<AUSProjectilePool>(AUSProjectilePool::StaticClass());
    }
    ProjectilePools.Add(DataAsset, Pool);
}