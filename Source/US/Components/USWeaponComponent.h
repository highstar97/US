#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USWeaponComponent.generated.h"

class AUSWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class US_API UUSWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UUSWeaponComponent();

	AUSWeapon* GetEquippedWeapon() const { return EquippedWeapon.Get(); }

	void EquipWeapon(AUSWeapon* NewWeapon);

	void UnequipWeapon();

	void UseWeapon();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AUSWeapon> DefaultWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AUSWeapon> EquippedWeapon;
};