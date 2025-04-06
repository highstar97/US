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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyVariable | Data Asset | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileDataAsset> ProjectileDataAsset;
};