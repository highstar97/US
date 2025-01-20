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
	UPROPERTY()
	TObjectPtr<AUSWeapon> EquippedWeapon;
};