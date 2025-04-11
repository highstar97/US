#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USProjectile.generated.h"

class UProjectileDataAsset;
class UCapsuleComponent;
class AUSCombatCharacter;

UCLASS()
class US_API AUSProjectile : public AActor
{
	GENERATED_BODY()
	
public:
    AUSProjectile();

    virtual void Tick(float DeltaTime) override;

    FORCEINLINE bool GetIsActive() const { return bIsActive; }

    void Init(const UProjectileDataAsset* ProjectileDataAsset);

    void ActivateProjectile(FVector Location, FVector Direction, AUSCombatCharacter* _OwnerCharacter);

    void DeactivateProjectile();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Component ", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCapsuleComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Data Asset ", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<const UProjectileDataAsset> ProjectileDataAsset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Projectile ", meta = (AllowPrivateAccess = "true"))
    FVector Velocity;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyVariable | Projectile ", meta = (AllowPrivateAccess = "true"))
    bool bIsActive;
    
    float ElapsedTime;

    TWeakObjectPtr<AUSCombatCharacter> OwnerCharacter;
};