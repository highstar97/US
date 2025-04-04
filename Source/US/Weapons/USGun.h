#pragma once

#include "CoreMinimal.h"
#include "Weapons/USWeapon.h"
#include "USGun.generated.h"

class AUSProjectilePool;
class UProjectileDataAsset;

UCLASS()
class US_API AUSGun : public AUSWeapon
{
	GENERATED_BODY()
	
public:
	AUSGun();

	virtual void Attack();

	virtual void Interact(ACharacter* Interactor) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon | Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileDataAsset> ProjectileDataAsset;
};