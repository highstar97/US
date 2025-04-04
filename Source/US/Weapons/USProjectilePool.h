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
    
    virtual void BeginPlay() override;

    AUSProjectile* GetAvailableProjectile();

    void InitProjectiles(UProjectileDataAsset* _ProjectileDataAsset);

private:
    // PoolSize를 NewPoolSize로 변경, (CurrentPoolSize < NewPoolSize)
    bool ResizePool(int32 CurrentPoolSize, int32 NewPoolSize);

private:
    UPROPERTY()
    TObjectPtr<UProjectileDataAsset> ProjectileDataAsset;

    UPROPERTY(EditAnywhere)
    int32 PoolSize = 20;

    UPROPERTY(VisibleAnywhere)
    TArray<TObjectPtr<AUSProjectile>> Pool;
};