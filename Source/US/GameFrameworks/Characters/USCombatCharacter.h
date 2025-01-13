#pragma once

#include "CoreMinimal.h"
#include "Characters/USCharacter.h"
#include "USCombatCharacter.generated.h"

class UUSWeaponComponent;

UCLASS()
class US_API AUSCombatCharacter : public AUSCharacter
{
	GENERATED_BODY()

public:
	AUSCombatCharacter();

	FORCEINLINE UUSWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	UUSWeaponComponent* WeaponComponent;
};