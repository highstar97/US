#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USProjectile.generated.h"

class UProjectileDataAsset;

UCLASS()
class US_API AUSProjectile : public AActor
{
	GENERATED_BODY()
	
public:
    AUSProjectile();

    virtual void Tick(float DeltaTime) override;

    FORCEINLINE bool GetIsActive() const { return bIsActive; }

    void InitProjectile(const UProjectileDataAsset* _ProjectileDataAsset);

    void ActivateProjectile(FVector Location, FVector Direction);

    void DeactivateProjectile();

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Projectile", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Projectile", meta = (AllowPrivateAccess = "true"))
    const UProjectileDataAsset* ProjectileDataAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Projectile", meta = (AllowPrivateAccess = "true"))
    FVector Velocity;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Projectile", meta = (AllowPrivateAccess = "true"))
    float ElapsedTime = 0.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon | Projectile", meta = (AllowPrivateAccess = "true"))
    bool bIsActive = false;
};