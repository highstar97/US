#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjectileSubsystem.generated.h"

class UProjectileDataAsset;
class AUSProjectile;
class AUSProjectilePool;

UCLASS()
class US_API UProjectileSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    // PoolMap에 ProjectileDataAsset이 있는지 확인하고, 없다면 추가
    void TryRegisterProjectileInPool(const UProjectileDataAsset* ProjectileDataAsset);

    // PoolMap에 ProjectileDataAsset이 있다면 해당 Pool에서 사용가능한 Projectile 리턴
    AUSProjectile* GetAvailableProjectile(UProjectileDataAsset* ProjectileDataAsset);

private:
    UPROPERTY()
    TMap<const UProjectileDataAsset*, AUSProjectilePool*> PoolMap;
};