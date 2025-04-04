#include "GameFrameworks/USLevelScriptActor.h"

#include "GameFrameworks/ProjectileSubsystem.h"

AUSLevelScriptActor::AUSLevelScriptActor()
{
}

void AUSLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

    if (UProjectileSubsystem* ProjectileSubsystem = GetWorld()->GetSubsystem<UProjectileSubsystem>())
    {
        for (TPair<UProjectileDataAsset*, AUSProjectilePool*> Pair : PoolMap)
        {
            ProjectileSubsystem->RegistProjectilePool(Pair.Key, Pair.Value);
        }

        ProjectileSubsystem->InitProjectilePools();
    }
}