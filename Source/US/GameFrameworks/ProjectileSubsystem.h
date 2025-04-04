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

    // World 생성 시 호출되어, Pools에 등록되어 있는 DataAsset의 Projectile을 초기 Pool 사이즈 만큼 초기화하는 함수
    void InitProjectilePools();

    AUSProjectile* GetAvailableProjectile(UProjectileDataAsset* DataAsset);

    void RegistProjectilePool(UProjectileDataAsset* DataAsset, AUSProjectilePool* Pool);

private:
    UPROPERTY()
    TMap<UProjectileDataAsset*, AUSProjectilePool*> ProjectilePools;
};