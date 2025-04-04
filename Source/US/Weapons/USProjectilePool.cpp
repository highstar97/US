#include "Weapons/USProjectilePool.h"

#include "Weapons/USProjectile.h"

AUSProjectilePool::AUSProjectilePool()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AUSProjectilePool::BeginPlay()
{
	Super::BeginPlay();
}

AUSProjectile* AUSProjectilePool::GetAvailableProjectile()
{
    for (AUSProjectile* Projectile : Pool)
    {
        if (!Projectile->GetIsActive())
        {
            return Projectile;
        }
    }

    ResizePool(PoolSize, 2*PoolSize);
    return GetAvailableProjectile();
}

void AUSProjectilePool::InitProjectiles(UProjectileDataAsset* _ProjectileDataAsset)
{
    ProjectileDataAsset = _ProjectileDataAsset;

    ResizePool(0, PoolSize);
}

bool AUSProjectilePool::ResizePool(int32 CurrentPoolSize, int32 NewPoolSize)
{
    if (CurrentPoolSize >= NewPoolSize) return false;
    PoolSize = NewPoolSize;

    Pool.Reserve(NewPoolSize);
    for (int32 i = CurrentPoolSize; i < NewPoolSize; ++i)
    {
        AUSProjectile* NewProjectile = GetWorld()->SpawnActor<AUSProjectile>(AUSProjectile::StaticClass());
        if (NewProjectile)
        {
            NewProjectile->InitProjectile(ProjectileDataAsset);
            Pool.Add(NewProjectile);
        }
    }
    return true;
}