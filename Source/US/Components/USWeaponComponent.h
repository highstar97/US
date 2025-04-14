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

	FORCEINLINE AUSWeapon* GetEquippedWeapon() const { return EquippedWeapon; }

	void EquipWeapon(AUSWeapon* NewWeapon);

	void UnequipWeapon();

protected:
	virtual void BeginPlay() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "MyVariable | Weapon | Need To Edit", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AUSWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleAnywhere, Category = "MyVariable | Weapon ", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AUSWeapon> EquippedWeapon;
};