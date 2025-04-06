#include "Weapons/USProjectilePool.h"

#include "Weapons/USProjectile.h"

AUSProjectilePool::AUSProjectilePool()
{
	PrimaryActorTick.bCanEverTick = false;
    
    PoolSize = 20;
}

void AUSProjectilePool::Init(const UProjectileDataAsset* _ProjectileDataAsset)
{
    ProjectileDataAsset = _ProjectileDataAsset;

    ResizePool(0, PoolSize);
}

AUSProjectile* AUSProjectilePool::GetAvailableProjectile()
{
    for (AUSProjectile* Projectile : Projectiles)
    {
        if (!Projectile->GetIsActive())
        {
            return Projectile;
        }
    }

    ResizePool(PoolSize, 2*PoolSize);
    return GetAvailableProjectile();
}

bool AUSProjectilePool::ResizePool(int32 CurrentPoolSize, int32 NewPoolSize)
{
    if (CurrentPoolSize >= NewPoolSize) return false;
    PoolSize = NewPoolSize;

    Projectiles.Reserve(NewPoolSize);
    for (int32 i = CurrentPoolSize; i < NewPoolSize; ++i)
    {
        AUSProjectile* NewProjectile = GetWorld()->SpawnActor<AUSProjectile>(AUSProjectile::StaticClass());
        if (NewProjectile)
        {
            NewProjectile->Init(ProjectileDataAsset);
            Projectiles.Add(NewProjectile);
        }
    }
    return true;
}