#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USProjectilePool.generated.h"

class AUSProjectile;
class UProjectileDataAsset;

UCLASS()
class US_API AUSProjectilePool : public AActor
{
	GENERATED_BODY()
	
public:
    AUSProjectilePool();

    // Pool의 ProjectileDataAsset을 설정하고, PoolSize에 맞게 Projectile을 생성
    void Init(const UProjectileDataAsset* _ProjectileDataAsset);

    // 현재 사용가능한 발사체 반환, 없다면 Pool을 2배로 늘린 후 사용가능한 발사체 반환
    AUSProjectile* GetAvailableProjectile();

private:
    // PoolSize를 NewPoolSize로 변경, (CurrentPoolSize < NewPoolSize)
    bool ResizePool(int32 CurrentPoolSize, int32 NewPoolSize);

private:
    UPROPERTY(VisibleAnywhere)
    int32 PoolSize;
    
    UPROPERTY()
    TObjectPtr<const UProjectileDataAsset> ProjectileDataAsset;

    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<AUSProjectile>> Projectiles;
};