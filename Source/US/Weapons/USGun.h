#pragma once

#include "CoreMinimal.h"
#include "Weapons/USWeapon.h"
#include "USGun.generated.h"

class UArrowComponent;

UCLASS()
class US_API AUSGun : public AUSWeapon
{
	GENERATED_BODY()
	
public:
	AUSGun();

	virtual void Attack();

	virtual void Interact(ACharacter* Interactor) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ArrowComponent;
};