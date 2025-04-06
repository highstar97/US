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

    void Init(const UProjectileDataAsset* ProjectileDataAsset);

    void ActivateProjectile(FVector Location, FVector Direction);

    void DeactivateProjectile();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Data Asset ", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<const UProjectileDataAsset> ProjectileDataAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Projectile ", meta = (AllowPrivateAccess = "true"))
    FVector Velocity;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Projectile ", meta = (AllowPrivateAccess = "true"))
    bool bIsActive;
    
    float ElapsedTime;
};